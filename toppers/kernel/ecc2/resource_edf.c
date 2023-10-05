/*
 *  TOPPERS Automotive Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2004-2006 by Witz Corporation, JAPAN
 * 
 *  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 */

/*
 *	リソース管理機能(ECC2)
 */

#include "osek_kernel.h"
#include "check.h"
#include "task.h"
#include "alarm.h"
#include "interrupt.h"
#include "resource.h"
#include "resource_info.h"
#include "edf_resource_manage.h"
#include "deadline.h"
#include "edf.h"


TickType dl_bu;
UINT8 rescb_used;


/*
 *  リソース管理機能の初期化
 */
void
resource_initialize(void)
{
	int res = 0;
	for(res = 0; res < tnum_resource; res++){
		rescb_prevres[res] = RESID_NULL;
	}
	ResourceType	resid;

	for (resid = 0; resid < tnum_resource; resid++) {
		rescb_prevpri[resid] = TPRI_NULL;
	}
}

/*
 *  リソースの獲得
 */
StatusType
GetResource(ResourceType resid)
{
	if (callevel == TCL_TASK) {
		rescb_bitmap[resid/16] |= RESMAP_BIT(resid%16);
		rescb_usingtask[resid] = runtsk;
		rescb_used++;
	}
	return(GetResource_edf(resid));
}

/*
 *  リソースの返却
 */
StatusType
ReleaseResource(ResourceType resid)
{
	if (callevel == TCL_TASK) {
		rescb_bitmap[resid/16] &= ~RESMAP_BIT(resid%16);
		rescb_usingtask[resid] = TSKID_NULL;
		rescb_used--;
	}
	return(ReleaseResource_edf(resid));
}


/*
 *	リソース獲得のEDF対応版
 */
StatusType
GetResource_edf(ResourceType resid)
{
	StatusType	ercd = E_OK;

	LOG_GETRES_ENTER(resid);
	CHECK_CALLEVEL(TCL_TASK | TCL_ISR2);
	CHECK_RESID(resid);

	lock_cpu();
	D_CHECK_ACCESS(rescb_prevpri[resid] == TPRI_NULL);
	rescb_prevpri[resid] = 1;
	if (callevel == TCL_TASK) {
		rescb_prevres[resid] = tcb_lastres[runtsk];
		tcb_lastres[runtsk] = resid;
		
		// rescb_used++;
		// rescb_bitmap[resid/16] |= RESMAP_BIT(resid%16);	//リソース獲得状況ビットマップを更新
		// rescb_usingtask[resid] = runtsk;
		
		rescb_prevdl[resid] = tcb_deadline[runtsk];
	}
	else {
		rescb_prevres[resid] = isrcb_lastres[runisr];
		isrcb_lastres[runisr] = resid;
	}

  exit:
	unlock_cpu();
	LOG_GETRES_LEAVE(ercd);
	return(ercd);

  error_exit:
	lock_cpu();
  d_error_exit:
	_errorhook_par1.resid = resid;
	call_errorhook(ercd, OSServiceId_GetResource);
	goto exit;
}

/*
 *	リソース解放のEDF対応版
 */
StatusType
ReleaseResource_edf(ResourceType resid)
{
	StatusType	ercd = E_OK;

	LOG_RELRES_ENTER(resid);
	CHECK_CALLEVEL(TCL_TASK | TCL_ISR2);
	CHECK_RESID(resid);

	if (callevel == TCL_TASK) {
		ResourceType res;
		TaskType tsk;
		UINT16 bitmap;
		
		CHECK_NOFUNC(tcb_lastres[runtsk] == resid);

		lock_cpu();
		// rescb_used--;
		tcb_lastres[runtsk] = rescb_prevres[resid];
		rescb_prevres[resid] = RESID_NULL;
		// rescb_bitmap[resid/16] &= ~RESMAP_BIT(resid%16);	//リソース獲得状況ビットマップを更新
		// rescb_usingtask[resid] = TSKID_NULL;
		
		//タスクのデッドラインを次に早いものに変更
		
		//*
		//簡易処理版
		//リソース解放時にprevdlよりデッドラインの早いタスクがあっても，探索せず元の値に戻る
		//そのため，複数のリソースを獲得していると正しく動かない場合がある
		
		tcb_deadline[runtsk] = rescb_prevdl[resid];		
		//*/
		
		/*
		//改良版
		//リソース解放時に獲得している他のリソースを共有しているタスクを探索し，よりデッドラインの早いタスクがあれば
		//そのタスクのデッドラインを継承する
		//バグがあって動かなかったが，直す時間がないので次に引き継ぐ人に任せます
		
		tcb_deadline[runtsk] = rescb_prevdl[resid];
		res = tcb_lastres[runtsk];							//リソースの参照を順にたどる
		while(res != RESID_NULL){							//リソースを最後までたどったら終了
			for(tsk = 0; tsk < tnum_task; tsk++){			//リソースを共有しているタスクを調べる
				bitmap = tinib_resource[tsk][( res-1 )/16+1] & RESMAP_BIT(res);	//そのタスクがリソースを共有しているか
				if(bitmap && ( cntcb_curval[tskcnt] < tcb_deadline[tsk] && tcb_deadline[tsk]< tcb_deadline[runtsk]) ||
							 ( cntcb_curval[tskcnt] > tcb_deadline[runtsk] && ( cntcb_curval[tskcnt] < tcb_deadline[tsk] || tcb_deadline[tsk] < tcb_deadline[runtsk] ))
					   	){	//タスクが同じリソースを共有していて，さらにデッドラインがリソース獲得タスクより早い場合
					tcb_deadline[runtsk] = tcb_deadline[tsk];	//そのデッドラインを継承する
				}
			}
			res = rescb_prevres[res];						//次のリソース
		}
		//*/
		
		////タスクを再キューイング
		if(nexttsk != TSKID_NULL && ( cntcb_curval[tskcnt] < tcb_deadline[nexttsk] && tcb_deadline[nexttsk]< tcb_deadline[runtsk]) ||
							 ( cntcb_curval[tskcnt] > tcb_deadline[runtsk] && ( cntcb_curval[tskcnt] < tcb_deadline[nexttsk] || tcb_deadline[nexttsk] < tcb_deadline[runtsk] ))
					   	){
			preempt_edf();
			dispatch();
		}
	}
	else {
		CHECK_NOFUNC(isrcb_lastres[runisr] == resid);

		lock_cpu();
		isrcb_lastres[runisr] = rescb_prevres[resid];
	}
	rescb_prevpri[resid] = TPRI_NULL;
  exit:
	unlock_cpu();
	LOG_RELRES_LEAVE(ercd);
	return(ercd);

  error_exit:
	lock_cpu();
	_errorhook_par1.resid = resid;
	call_errorhook(ercd, OSServiceId_ReleaseResource);
	goto exit;
}

/*
 *	デッドラインを更新したタスクが共有しているリソースが使用中だった場合
 *	使用しているタスクのデッドラインを短くする
 *	複数のリソースが使用中の場合、IDが大きいものから優先される
 */
void ref_deadline(TaskType tskid)
{
	
	//獲得済みのリソースが存在する場合
	if( rescb_used > 0 ){
	
		//ビットマップのどのビットが立っているかを調べるための配列
		static const UINT16 search_table[] = { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
											   0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 };
		//リソース獲得状況ビットマップ配列の要素数
		
		ResourceType resid;				// リソースID
		UINT16 bitmap=0;				// リソース獲得状況ビットマップと，リソース共有ビットマップの論理積
		TaskType using = TSKID_NULL;	// リソースを獲得しているタスクのID
		int i=0;						// リソースビットマップ調査用while文のインクリメント
		
		//タスクが共有しているリソースが獲得済みかどうかを調べる
		for( i=0; i < res_arr; i++ ){
			
			//タスクが共有しているリソースを表すビットマップと
			//現在使用されているリソースを表すビットマップの論理積をとることで
			//タスクが共有しているリソースの中に使用中のものがないかを調べる
			bitmap = tinib_resource[tskid][i] & rescb_bitmap[i];
			
			//タスクが共有しているリソースの中に使用中のものがあった場合
			if(bitmap){
			
				//獲得されているリソースを調べる
				for( resid = 0; resid < 16; resid++ ){
					if( bitmap & search_table[resid]){
						//獲得しているタスクを調べる
						using = rescb_usingtask[i*16 + resid];
						
						//リソース使用タスクと更新したタスクが同じ場合
						//（リソースを獲得しているタスクのデッドラインが更新された場合），
						//そのタスクが最初に獲得したリソースの領域に格納された
						//デッドラインの情報を更新し，タスクのデッドラインを元に戻す
						if(tskid == using){
							int res = tcb_lastres[tskid];
							while( rescb_prevres[res] != RESID_NULL ){
								res = rescb_prevres[res];
							}
							rescb_prevdl[res] = tcb_deadline[using];
							tcb_deadline[using] = dl_bu;
						}
						else 
						//それ以外の場合で
						//今デッドラインを更新したタスクより
						//リソース獲得中のタスクの方がデッドラインが短い場合は
						//リソース獲得中タスクのデッドラインを短くする
						if( ( cntcb_curval[tskcnt] < tcb_deadline[tskid] && tcb_deadline[tskid]< tcb_deadline[using]) ||
							 ( cntcb_curval[tskcnt] > tcb_deadline[using] && ( cntcb_curval[tskcnt] < tcb_deadline[tskid] || tcb_deadline[tskid] < tcb_deadline[using] ))
					   	){
							tcb_deadline[using] = (tcb_deadline[tskid]==0)?
													cntinib_maxval2[tskcnt]-1 :( tcb_deadline[tskid] - 1);
						}
					}
				}
			}
		}
	}
}
