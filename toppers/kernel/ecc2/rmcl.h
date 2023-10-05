#ifndef _RMCL_H_
#define _RMCL_H_
#define TPRI_CRITICALTASK TPRI_MAXTASK
#ifndef PRIMAP_BIT
#define	PRIMAP_BIT(pri)		(1u << (pri))
#endif /* PRIMAP_BIT */
/* レディキュー用変数
 * task.cにて用いられているものをexternとして利用 */
extern TaskType ready_queue_first[];	/* レディキューの先頭タスク */
extern TaskType ready_queue_last[];	/* レディキューの最後尾タスク */
extern UINT16 ready_primap;	/* レディキューの格納状況ビットマップ */

/***** 変数 *****/
extern TaskType crtsk;	/* クリティカルタスクID */

extern BOOL is_critical(TaskType tskid);
extern BOOL search_criticaltsk();
extern void manage_resource();
extern BOOL make_runnable_rmcl(TaskType tskid);
extern void search_schedtsk_rmcl(void);
extern StatusType Schedule_rmcl(void);
/* レディキュー操作用関数
 * task.cにて記述されている */
extern void	ready_insert_first(Priority pri, TaskType tskid);
extern TaskType	ready_delete_first(Priority pri);

#endif
