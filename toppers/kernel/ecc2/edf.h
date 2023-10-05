#ifndef _EDF_H_
#define _EDF_H_

// /*	プロトタイプ宣言	*/
// /* アスペクト内で使用する関数 */
Inline TickType add_tick(TickType almval, TickType incr, TickType maxval2);
Inline TickType diff_tick(TickType val1, TickType val2, TickType maxval2);
Inline void enqueue_task(TaskType tskid);
Inline void dequeue_task(TaskType tskid);
/* for advices in task.c */
Inline TaskType ready_delete_first_edf(void);
extern void task_initialize_edf(void);
extern BOOL make_runnable_edf(TaskType tskid);
extern void search_schedtsk_edf(void);
extern void preempt_edf(void);
/* for advices in task_manage.c */
extern StatusType Schedule_edf(void);

extern TaskType tcb_prev[]; 				
extern TaskType nexttsk;					//次に実行されるタスク
extern CounterType tskcnt;

#endif
