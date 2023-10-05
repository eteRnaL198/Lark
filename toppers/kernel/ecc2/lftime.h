#ifndef _LFTIME_H_
#define _LFTIME_H_

extern const TickType tinib_wstexetm[]; /* タスクの最悪実行時間 */
extern TickType tcb_lftexetm[]; /* タスクの残り実行時間 */
extern TickType tcb_exebgntm[]; /* タスクの実行開始時間 */

Inline TickType diff_tick(TickType val1, TickType val2, TickType maxval2);

#endif
