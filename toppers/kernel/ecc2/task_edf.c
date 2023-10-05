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
 *	タスク管理モジュール(ECC2)
 */

#include "osek_kernel.h"
#include "check.h"
#include "task.h"
#include "resource.h"
#include "cpu_context.h"
#include "alarm.h"
#include "deadline.h"
#include "resource_info.h"
#include "edf.h"
#include "edf_resource_manage.h"
// #include "added_field.h"

TaskType nexttsk;	
CounterType tskcnt;
// TickType tcb_deadline[TNUM_TASK];
// TickType rescb_prevdl[TNUM_TASK];
// TaskType tcb_prev[TNUM_TASK];
// UINT16 rescb_bitmap[RES_ARR];
// TaskType rescb_usingtask[RES_ARR*TNUM_RESOURCE];
// const AlarmType tinib_almid[] = {0,1};
// const TickType tinib_deadline[TNUM_TASK] = {10000,10000};
// const TickType tinib_deadline[TNUM_TASK] = {5,10000};
// const UINT16 tinib_resource[TNUM_TASK][RES_ARR] = {{0x0003},{0x0003}};
// const UINT8 res_arr = RES_ARR;

/*
 *  スタティック関数のプロトタイプ宣言
 */
void	ready_insert_first(Priority pri, TaskType tskid);
void	ready_insert_last(Priority pri, TaskType tskid);
TaskType	ready_delete_first(Priority pri);
Priority	bitmap_search(UINT16 bitmap);

/*
 *  レディキュー
 *
 *  レディキューには実行可能状態のタスクのみをつなぐこととし，実行状態
 *  のタスクはレディキューからは外す．厳密には，schedtsk をレディキュー
 *  から外す（割込み処理中には，runtsk がレディキューから外れているとは
 *  限らない）．
 *  レディキューは，優先度毎の単方向リンクキューで構成する．レディキュー
 *  の先頭のタスクIDを ready_queue_first に，末尾のタスクID を
 *  ready_queue_last に保持する．レディキューが空の時は，ready_queue_first 
 *  を TSKID_NULL とし，ready_queue_last は不定とする．
 */
TaskType ready_queue_first[TNUM_PRIORITY];
TaskType ready_queue_last[TNUM_PRIORITY];

/*
 *  レディキューの先頭への挿入
 */
void
ready_insert_first(Priority pri, TaskType tskid)
{

}

/*
 *  レディキューの末尾への挿入
 */
void
ready_insert_last(Priority pri, TaskType tskid)
{

}

/*
 *  レディキューの先頭タスクの削除
 */
TaskType
ready_delete_first(Priority pri)
{
	return ( ready_delete_first_edf() );

}

/*
 *  ビットマップサーチ関数
 *
 *  bitmap 内の 1 のビットの内，最も上記（左）のものをサーチし，そのビ
 *  ット番号を返す．ビット番号は，最下位ビットを 0 とする．bitmap に 0
 *  を指定してはならない．この関数では，優先度が16段階以下であることを
 *  仮定し，bitmap の下位16ビットのみをサーチする．
 *  ビットサーチ命令を持つプロセッサでは，ビットサーチ命令を使うように
 *  書き直した方が効率が良いだろう．このような場合には，cpu_insn.h で
 *  ビットサーチ命令を使った bitmap_search を定義し，CPU_BITMAP_SEARCH 
 *  をマクロ定義すればよい．また，ビットサーチ命令のサーチ方向が逆など
 *  の理由で優先度とビットとの対応を変更したい場合には，PRIMAP_BIT を
 *  マクロ定義すればよい．
 *  また，標準ライブラリに ffs があるなら，次のように定義して標準ライ
 *  ブラリを使った方が効率が良い可能性もある．
 *	#define PRIMAP_BIT(pri)	(0x8000u >> (pri))
 *	#define	bitmap_search(bitmap) (16 - ffs(bitmap))
 *  μITRON仕様とは優先度の意味が逆のため，サーチする方向が逆になって
 *  いる．bitmap_search を置き換える場合には，注意が必要である．
 */
#ifndef PRIMAP_BIT
#define	PRIMAP_BIT(pri)		(1u << (pri))
#endif /* PRIMAP_BIT */

#ifndef CPU_BITMAP_SEARCH

Priority
bitmap_search(UINT16 bitmap)
{
	return((Priority)0);

}

#endif /* CPU_BITMAP_SEARCH */

/*
 *  実行状態のタスク
 */
TaskType	runtsk;

/*
 *  最高優先順位タスク
 */
TaskType	schedtsk;

/*
 *  レディキュー中の最高優先度
 */
Priority	nextpri;

/*
 *  レディキューに入っているタスクの優先度のビットマップ
 *
 *  レディキューが空の時（実行可能状態のタスクが無い時）は 0 にする．
 */
UINT16	ready_primap;

/*
 *  タスク管理モジュールの初期化
 */
void
task_initialize(void)
{
	TaskType	tskid;
	rescb_used = 0;

  for(tskid = 0; tskid < tnum_task; tskid++) {
    tcb_deadline[tskid] = (TickType)0x0000;
  }
	task_initialize_edf();

}

/*
 *  タスクの起動
 *
 *  TerminateTask や ChainTask の中で，自タスクに対して make_active を
 *  呼ぶ場合があるので注意する．
 */
BOOL
make_active(TaskType tskid)
{
	dl_bu = tcb_deadline[tskid];
  update_deadline(tskid);
 	ref_deadline(tskid);


	tcb_curpri[tskid] = tinib_inipri[tskid];
	if (tskid < tnum_exttask) {
		tcb_curevt[tskid] = EVTMASK_NONE;
		tcb_waievt[tskid] = EVTMASK_NONE;
	}
	tcb_lastres[tskid] = RESID_NULL;
	activate_context(tskid);
	return(make_runnable(tskid));
}

/*
 *  実行できる状態への移行
 */
BOOL
make_runnable(TaskType tskid)
{
	return (make_runnable_edf(tskid));

}

/*
 *  最高優先順位タスクのサーチ
 */
void
search_schedtsk(void)
{
	search_schedtsk_edf();
}

/*
 *  タスクのプリエンプト
 */
void
preempt(void)
{
	preempt_edf();

}
/********以下カスタマイズのための関数*************/
Inline TickType
add_tick(TickType almval, TickType incr, TickType maxval2)
{
  if (incr <= (maxval2 - almval)) {
    return(almval + incr);
  }
  else {
    return(almval + incr - (maxval2 + 1));
  }
}
/*
 *  タスクのデッドラインを更新する関数
 */
Inline void
update_deadline(TaskType tskid)
{
  AlarmType almid = tinib_almid[tskid];
  tcb_deadline[tskid] = add_tick(almcb_almval[almid], tinib_deadline[tskid], cntinib_maxval2[alminib_cntid[tinib_almid[tskid]]]);
}

/*
 * Tick値の比較し差を返す
 */
Inline TickType
diff_tick(TickType val1, TickType val2, TickType maxval2)
{
  if (val1 >= val2) {
    return(val1 - val2);
  }
  else {
    /*
     *  下の計算式で，val1 - val2 と maxval2 + 1 が TickType で表せ
     *  る範囲を超える場合があるが，オーバフローしても求まる値は正
     *  しいため差し支えない．
     */
    return(val1 - val2 + (maxval2 + 1));
  }
}

/*
 *  タスクキューへの挿入
 *
 *  tskid で指定されるタスクを，タスクキュー[0]に挿入する．
 *  また，タスクキューに同じデッドラインのタスクがある場合には，
 *  その末尾に挿入する（先頭でも差し支えないと思われる）．
 */
Inline void
enqueue_task(TaskType tskid)
{
	TaskType	next, prev;
	TickType	curval,dl;
	
	/*
	 *  挿入場所のサーチ
	 */
	next = nexttsk;
	prev = TSKID_NULL;
	curval = cntcb_curval[tskcnt];
	dl = tcb_deadline[tskid];
	
	if(curval<dl){
		while ( next != TSKID_NULL && ((curval <= tcb_deadline[next])
					&& (tcb_deadline[next] <= dl))) {
			prev = next;
			next = tcb_next[prev];
		}
	}
	else {
		while ( next != TSKID_NULL && ((curval <= tcb_deadline[next])
					|| (tcb_deadline[next] <= dl))) {
			prev = next;
			next = tcb_next[prev];
		}
	}

	/*
	 *  キューのつなぎ換え処理
	 */
	tcb_next[tskid] = next;
	tcb_prev[tskid] = prev;
	if (prev != TSKID_NULL) {
		tcb_next[prev] = tskid;
	}
	else {
		nexttsk = tskid;
	}
	if (next != TSKID_NULL) {
		tcb_prev[next] = tskid;
	}
}


/*
 *  タスクキューからの削除
 *
 *  TSKID で指定されるタスクを，タスクキュー[0]から削除する．
 */
Inline void
dequeue_task(TaskType tskid)
{
	TaskType	next, prev;

	next = tcb_next[tskid];
	prev = tcb_prev[tskid];
	if (prev != TSKID_NULL) {
		tcb_next[prev] = next;
	}
	else{
		nexttsk = next;
	}
	if (next != TSKID_NULL) {
		tcb_prev[next] = prev;
	}
	tcb_next[tskid] = tskid;
}


/*
 *	スケジューリング関数(EDF)
 */
Inline void
search_schedtsk_edf(void)
{
	schedtsk = (nexttsk == TSKID_NULL)?
				TSKID_NULL : ready_delete_first_edf();
}

Inline BOOL
make_runnable_edf(TaskType tskid)
{
	// タスク状態を実行可能状態へ遷移させる
	tcb_tstat[tskid] = TS_RUNNABLE;

	// 実行中タスクがある場合
	if ( schedtsk != TSKID_NULL) {
		// 現在のティック値， デッドライン
		TickType curval,dl;
		// 現在ティック値を取得
		curval = cntcb_curval[tskcnt];
		// 新タスクのデッドライン値の取得
		dl = tcb_deadline[tskid];
		// (現在ティック < 実行中タスクのデッドライン < 新タスクのデッドライン) ||
		// (現在ティック > 新タスクのデッドライン) && (現在ティック < 実行中タスクのデッドライン || 実行中タスクのデッドライン < 新タスクのデッドライン) )
		// 実行中タスクがデッドラインが近い場合 TRUE
		// 新タスクがデッドラインに近い場合 FALSE
		if((curval < tcb_deadline[schedtsk] && tcb_deadline[schedtsk] < dl ) ||
			(curval > dl && (curval < tcb_deadline[schedtsk] || tcb_deadline[schedtsk] < dl )) 
		){
			//  schedtsk のデッドラインがtskid以下の場合，tskid を
			//  レディキューに入れる．
			enqueue_task( tskid );
			return( FALSE );
		}
		//  tskid の方がデッドラインが短い場合，schedtsk をレディキュー
		//  に入れ，tskid を新しい schedtsk とする．
		enqueue_task( schedtsk );
	}
	schedtsk = tskid;
	return( TRUE );

}

void
preempt_edf(void)
{
	assert(runtsk == schedtsk);
	enqueue_task(schedtsk);
	search_schedtsk();
}


/*
 *  タスク管理モジュールの初期化（EDF対応版）
 */
void
task_initialize_edf(void)
{
	TaskType	tskid;

	runtsk = TSKID_NULL;
	schedtsk = TSKID_NULL;
	nexttsk = TSKID_NULL;
	
	/* タスクレディキューは0のみ使用する */

	//獲得リソースを初期化
	for (tskid = 0; tskid < tnum_task; tskid++) {
		tcb_lastres[tskid] = RESID_NULL;
	}
	
	tskcnt = alminib_cntid[tinib_almid[(TaskType)0]];
	for (tskid = 0; tskid < tnum_task; tskid++) {
		tcb_actcnt[tskid] = 0;
		//タスクキューの初期化
		tcb_next[tskid] = tskid;
		// 絶対デッドライン算出
		// update_deadline(tskid);
		
		if ((tinib_autoact[tskid] & appmode) != APPMODE_NONE) {
			(void)make_active(tskid);
			tcb_tstat[tskid] = TS_RUNNABLE;
		}
		else {
			tcb_tstat[tskid] = TS_DORMANT;
		}
	}
}

/*
 *  レディキューの先頭タスクの削除(EDF)
 */
Inline TaskType
ready_delete_first_edf()
{
	TaskType	first;

	first = nexttsk;
	assert(first != TSKID_NULL);
	nexttsk = tcb_next[first];
	return(first);
}
