/*
 *  TOPPERS Automotive Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
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

/*ヘッダファイル*/
#include "osek_kernel.h"

/*
 *  プロセッサ依存モジュール（H8S用）
 */

/*
 *  CPUロックにかかわる変数.
 *
 *  本OSカーネルでは割込み制御をIフラグ及びIPLの双方を用いて行う
 *  ことを前提とする.このためIフラグまたはI0〜I2(IPL)のどちらかを
 *  選択するH8Sでは不足機能をソフトウェアで補う必要がある.
 *
 *  初期値：起動時は割込み全禁止状態である.
 *  これは割込み全許可状態(I0〜I2=0)時にlock_cpu()を実行した状態と同じと
 *  考えられる.このため「disint_flag=TRUE」・「saved_intpri=0」とする.
 */
UINT8	saved_intpri;	/* dis_int状態での保持ipl		*/
UINT8	disint_flag;	/* dis_int状態管理フラグ		*/

/*
 *  プロセッサ依存の初期化
 */
void
cpu_initialize(void)
{
	saved_intpri = 0;	/* dis_int状態での保持ipl		*/
	disint_flag = TRUE;	/* dis_int状態管理フラグ		*/
}

/*
 *  プロセッサ依存の終了処理
 */
void
cpu_terminate(void)
{
}



