#ifndef _DEADLINE_H_
#define _DEADLINE_H_

/***** 初期値 *****/
extern const TickType tinib_deadline[];	/* タスクの相対デッドライン */
extern const AlarmType tinib_almid[];	/* 周期タスクに対応したアラームID */

/***** 変数 *****/
extern TickType tcb_deadline[];	/* タスクの絶対デッドライン */

extern void update_deadline(TaskType);

#endif
