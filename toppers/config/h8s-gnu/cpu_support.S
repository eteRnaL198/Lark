;
;   TOPPERS Automotive Kernel
;       Toyohashi Open Platform for Embedded Real-Time Systems
;       Automotive Kernel
; 
;  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
;                              Toyohashi Univ. of Technology, JAPAN
;  Copyright (C) 2003 by Naoki Saito
;             Nagoya Municipal Industrial Research Institute, JAPAN
;  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
;              Graduate School of Information Science, Nagoya Univ., JAPAN
;  Copyright (C) 2004-2006 by Witz Corporation, JAPAN
; 
;  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
;  によって公表されている GNU General Public License の Version 2 に記
;  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
;  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
;  利用と呼ぶ）することを無償で許諾する．
;  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
;      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
;      スコード中に含まれていること．
;  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
;      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
;      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
;      の無保証規定を掲載すること．
;  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
;      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
;      と．
;    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
;        作権表示，この利用条件および下記の無保証規定を掲載すること．
;    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
;        報告すること．
;  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
;      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
; 
;  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
;  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
;  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
;  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
; 
;


;
;	プロセッサ依存モジュール アセンブリ言語部（H8S用）
;
	.h8300s

;	外部参照宣言
	.global	_runtsk
	.global	_schedtsk
	.global	_tcxb_pc
	.global	_tcxb_sp
	.global	_tinib_task
	.global	_callevel
	.global	_runisr
	.global	_tinib_exepri
	.global	_tcb_curpri
	.global	_call_pretaskhook
	.global	_call_posttaskhook
	.global	_PreTaskHook
	.global	_PostTaskHook
	.global	_saved_intpri

;	外部公開宣言
	.global	_dispatch
	.global	_start_dispatch
	.global	_exit_and_dispatch
	.global	_activate_r
	.global	_interrupt

;	定数定義
;	_MACRO_ONLYを定義してヘッダファイルのインクルード可能？
#define	CL_TASK		0x01
#define	CL_ISR2		0x02
#define	ID_INVAL	0xFF
#define	TRUE		0x01
#define	FALSE		0x00
#define	EXR_OFFSET	24
#define	EXR_MSK		0x07

	.section .text
	.align 1


;
;	タスクディスパッチャ
;
;	呼び出し条件:
;		割込み：EXRのI0〜I2=7 (CPUロック状態)
;		コンテキスト：callevel=1(タスクコンテキスト)
;		スタック： タスクスタック
;
_dispatch:
	push	er4						; スタックへレジスタ保存
	push	er5						; 呼び出し規約を考慮すると0〜3は呼び出し側が
	push	er6						; 責任を持つ(スクラッチレジスタ)ため退避不要
	sub.l	er0, er0
	mov.b	@_runtsk, r0l			; er0 <- runtsk
	shll.l	#2, er0					; 1Byte->4Byte
	mov.l	sp, @(_tcxb_sp,er0)		; スタックポインタをTCBに保存
	mov.l	#dispatch_r, er1
	mov.l	er1, @(_tcxb_pc,er0)	; 実行再開番地をTCBに保存
	jmp		dispatcher

;
;	呼び出し条件:
;		割込み：EXRのI0〜I2=7 (CPUロック状態)
;		コンテキスト：callevel=1(タスクコンテキスト)
;		スタック： タスクスタック
;
dispatch_r:
	pop		er6
	pop		er5
	pop		er4						; タスクスタックからレジスタ復帰
	rts								; dispatch 呼び出し元へ戻る.

;
;	タスク起動時処理
;
;	ここでは, CPUロック解除状態にし, タスクを起動する.
;
;	呼出条件:
;		割込み：EXRのI0〜I2=7 (CPUロック状態)
;		コンテキスト：callevel=1(タスクコンテキスト)
;		スタック： タスクスタック
;
_activate_r:
	sub.l	er0, er0
	mov.b	@_runtsk, r0l			; 実行開始タスクID
	mov.b	@(_tinib_exepri,er0), r1l
	mov.b	r1l,@(_tcb_curpri,er0)
	mov.b	#FALSE, r1l
	mov.b	r1l, @_disint_flag		; 割込み管理フラグクリア(実態(exr)に追従)
	ldc.b	#0x00, exr				; 割込み許可
	shll.l	#2, er0          		; 1Byte->4Byte
	mov.l	@(_tinib_task,er0), er1
	jmp		@er1

;
;	dispatcher呼び出し条件:
;		・すべてのタスクのコンテキストは保存されている.
;		・EXRのI0〜I2=7 (CPUロック状態),
;		・コンテキストはカーネル起動時を除きタスクコンテキスト(callevel=1)
;				callevelの初期値は1？
;		起動時は非タスクコンテキスト(callevel=?)で, その場合にも対応.
;	dispatcher 呼出時のスタック:
;		_dispatch からきた場合: タスクスタック
;		_exit_and_dispatch からきた場合: タスクスタック
;		_start_dispatch からきた場合: 割込みスタック
;		ret_int からきた場合: タスクスタック
;		pre_idle での割込み待ちからきた場合: 割込みスタック
;
_exit_and_dispatch:
dispatcher:
	mov.l	#_PostTaskHook, er1		; mov命令でポストタスクフック無効時はZ=1となる
	beq		_start_dispatch			; ポストタスクフック有効？
	jsr		@_call_posttaskhook

_start_dispatch:
	sub.l	er0, er0
	mov.b	@_schedtsk, r0l			; 
	mov.b	r0l, @_runtsk			; schedtsk を runtsk に
	cmp.b	#ID_INVAL, r0l
	beq		pre_idle				; schedtsk がなければ割込み待ち
	shll.l	#2, er0					; 1Byte->4Byte
	mov.l	@(_tcxb_sp,er0), sp		; タスクスタックポインタを復帰
	mov.l	@(_tcxb_pc,er0), er4	; 実行再開番地を取得

	mov.l	#_PreTaskHook, er1		; mov命令でプレタスクフック無効時はZ=1となる
	beq		dispatch_task			; プレタスクフック有効？
	jsr		@_call_pretaskhook

dispatch_task:
	jmp		@er4			 		; 実行再開番地へジャンプ
;
;	ここからは schedtsk がない場合
;
pre_idle:
	mov.l	#__stack_top, sp		; 割込み用のスタックへ切替え
	mov.b	#CL_ISR2, r0l
	mov.b	r0l, @_callevel			; 非タスクコンテキスト
	mov.b	#FALSE, r1l
	mov.b	r1l, @_disint_flag		; 割込み管理フラグクリア

	; idle_loop内で割込み禁止した状態の時に
	; _disint_flagを操作することはない！！
	; このため、実態(exr)に追従はさせない。
idle_loop:
	ldc.b	#0x00, exr				; 割込み許可

;	スタンバイモード処理
; 本来ならここでのNOPは1回でよいのだが、
; 「ldc命令後、3ステート間は割込みを受け付けれない」と
; マニュアルに記載があったため、
; NOPを4つ以上実行する。
; 実測上、4ステート分のNOPでは割込みが受け付けれなかったため、
; 5ステート分NOPを行う
	nop
	nop
	nop
	nop
	nop

	ldc.b	#0x07, exr				; 割込み禁止
	mov.b	@_schedtsk, r0l			; 
	cmp.b	#ID_INVAL, r0l
	beq		idle_loop

	mov.b	#TRUE, r1l
	mov.b	r1l, @_disint_flag		; 割込み管理フラグセット
	mov.b	#0x00, r1l				; 仮想的にここで
	mov.b	r1l, @_saved_intpri		; 作成する
	mov.b	#CL_TASK, r0l
	mov.b	r0l, @_callevel			; タスクコンテキストに戻す
	jmp		@_start_dispatch		; _start_dispatch へ戻る

;
;  割込みハンドラ出口処理(ディスパッチ要求あり)
;
;
;	呼び出し条件:
;		割込み：EXRのI0〜I2=7 (CPUロック状態)
;		コンテキスト：callevel=1(タスクコンテキスト)
;		スタック：タスクスタック
;		タスクコンテキストはer0,er1,er2,er3がスタックに積まれた状態
;		注意：_interrupt:からしか実行されないものとし、
;		      r0lには既に_runtskの値が格納されているものとする。
;
;	ディスパッチ後のCPUアンロック処理に対応するため,disint_flag及び
;	saved_intpriに値を設定する.
;	・disint_flag:CPUロック状態のためTRUEを設定
;	・saved_intpri:下記前提条件より0を設定
;	  1.通常タスク動作中はI0〜I2=0であり、割込み/ディスパッチ後もI0〜I2=0である.
;	  2.リソース取得においてI0〜I2!=0の時に割込みが発生した場合,
;	    実行可能状態の各タスクのプロセッシングレベルはタスクレベルである.
;	    割込み発生時に実行していたタスクのプロセッシングレベルは
;	    割込みレベル(I0〜I2!=0)のためディスパッチは起こらない.
;	  3.これらよりディスパッチが起こる時はI0〜I2=0として問題ない.
;
ret_int:
	push	er4					; スタックへ_interrupt:で保持していないレジスタ保存
	push	er5
	push	er6
	mov.b	#TRUE, r1l			; ディスパッチ後の
	mov.b	r1l, @_disint_flag	; CPUロック状態を
	mov.b	#0x00, r1l			; 仮想的にここで
	mov.b	r1l, @_saved_intpri	; 作成する
	mov.b	#0, r0h
	extu.l	er0					; <bit8〜31> of er0 = 0
	shll.l	#2, er0				; 1Byte->4Byte
	mov.l	sp, @(_tcxb_sp,er0)	; スタックポインタをTCBに保存
	mov.l	#ret_int_r, er1
	mov.l	er1, @(_tcxb_pc,er0); 実行再開番地をTCBに保存
	jmp.b	dispatcher

;
;	呼び出し条件:
;		割込み：EXRのI0〜I2=7 (CPUロック状態)
;		コンテキスト：callevel=1(タスクコンテキスト)
;		スタック： タスクスタック
;		タスクコンテキストはer0,er1,er2,er3,er4,er5,er6がスタックに積まれた状態
;
;	ディスパッチ要因の実行はCPUロック状態で行われる.このため,割込み管理フラグを
;	クリアする必要がある(本ret_int_rは割込みでプリエンプトしたタスクへの戻り
;	処理でありOSが行うCPUアンロック処理などがないため).なお,CPUアンロック状態
;	におけるsaved_intpriの値は不定のため操作は行わない.
;
ret_int_r:
	mov.b	#FALSE, r0l			; CPUアンロック処理
	mov.b	r0l, @_disint_flag	; 割込み管理フラグクリア
	pop		er6					; レジスタ復帰
	pop		er5
	pop		er4

	; MACH/MACLレジスタ退避
	pop		er3
	ldmac	er3, mach
	pop		er3
	ldmac	er3, macl

	pop		er3
	pop		er2
	pop		er1
	pop		er0
	rte							; タスクへ戻る


;
;	割込み出入口処理(アセンブリ言語記述部分)
;
;	呼出し条件:
;		割込み：EXRのI0〜I2=7 (CPUロック状態), r3lに受付けた割込みの優先度を保持
;		コンテキスト：callevel=1(タスクコンテキスト)
;		スタック：多重割り込みなら割込みスタック, そうでなければタスクスタック
;		ユーザ割込みルーチン：er2 に保持
;		その他：r0h 本割込みのID保持
;
;	 割込み入り口（割込み禁止前）における割込み発生判定:
;		 H8Sでは割込み受付直後に割込み禁止になっていないため、割込みA
;		 の入口処理中に別の割込みBが入る可能性がある。（これはハード
;		 ウェアのアーキテクチャ上避けようがない。）割込みハンドラB内
;		 でタスク切り替えを起こすようなサービスコールを呼ぶと割込みB
;		 の出口処理で別のタスクにディスパッチしてしまい、タスク2から
;		 元のタスクに戻ってくるまで、割込みAの処理が遅れてしまう。
;		 また、割込みAがレベルトリガだと2回検出されてしまう問題もある。
;		 これを防ぐため、スタックに積んである戻り先のEXRとsaved_intpri
;		 の値を比較して、入口処理中に割込みが入らなかったかチェックし
;		 ている。ディスパッチする前のタイミングで判別しているので、
;		 saved_intpriが書き換えられている心配はない。
;
;
;	レジスタがスタック上にどのように保存されているかを以下に示す.
;	この図では上が低位, 下が高位のアドレスで, スタックは下から
;	上方向に向かって積み上げられるものとする.
;
;	--------------------------
;	|       er6(4byte)       |
;	|                        |
;	-------------------------
;	|       er5(4byte)       |
;	|                        |
;	-------------------------
;	|       er4(4byte)       |
;	|                        |
;	-------------------------
;
;	これより上はディスパッチ要求時にret_intにてスタックに積まれるレジスタ.
;	これより下は割り込み発生時にスタックに積まれるレジスタ.
;
;	-------------------------
;   |       MACH(4byte)      |
;   |                        |
;	-------------------------
;	|       MACL(4byte)      |
;	|                        |
;	-------------------------
;	|       er3(4byte)       |
;	|                        |
;	-------------------------
;	|       er2(4byte)       |
;	|                        |
;	-------------------------
;	|       er1(4byte)       |
;	|                        |
;	-------------------------
;	|       er0(4byte)       |
;	|                        |
;	-------------------------
;	|       EXR(1byte)       |
;	-------------------------
;	|       TEMP(1byte)      |
;	-------------------------
;	|       CCR(1byte)       |
;	-------------------------
;	|       PC(3byte)        |
;	-------------------------

;	ハンドラからリターンした後は, 多重割込みでなく, 
;	ディスパッチ要求がある時(schedtsk != runtsk)に，
;	ret_int へ分岐する．
;
;	多重割込みかどうかはcallevelの値で判定する.
;	callevel != 1 ならば多重割込みであると判定する.
;
;	割込み入口処理から継続してdisint_flag及びsaved_intpriの操作は行わない.
;	ディスパッチが起こらない限り上記変数の操作は不要.
;	・「割込み発生時にexr値をr3lに保持して割込み禁止→ユーザルーチン実行直前に
;	  r3lからexr値を復元することで割込み許可」と完結しており操作不要.
;	・「ユーザルーチン実行後に割込み禁止→rte命令にてexr値が復元され
;	  割込み許可」と完結しており操作不要.
;	ディスパッチが起きた時の対応はret_int及びret_int_rで対応する.
;
_interrupt:
	stmac	macl, er1		; MACLをスタックへ退避
	push	er1
	stmac	mach, er1		; MACHをスタックへ退避
	push	er1

	mov.b	@_runisr, r0l	; 実行中割込みIDを保持
	mov.b	r0h, @_runisr	; 本割込みIDを設定
	mov.b	@_callevel, r0h
	cmp.b	#CL_TASK, r0h	; 多重割り込みかどうか
	bne		int_from_int	; 0でなければ多重割込み

	; 初段の割込み(タスクから)
	mov.l	sp, er1			; スタックポインタを取り出し
	mov.l	#__stack_top, sp; 割込み用のスタックへ切替える
	push.l	er1				; タスクスタックポインタを保持

int_from_int:				; 多重割込み
	push.w	r0				; runisrとcallevelをスタックに保持
	mov.b	#CL_ISR2, r0h	; やや無駄かな
	mov.b	r0h, @_callevel	; 実行レベルをISR2に設定
	ldc.b	r3l, exr		; 高優先度割込み許可
	jsr		@er2			; Cルーチン呼び出し
	ldc.b	#0x07, exr		; 割込み禁止
	pop.w	r0				; runisrとcallevelをスタックから復帰
	mov.b	r0h, @_callevel	; 実行レベルをスタックから復帰
	mov.b	r0l, @_runisr	; 実行中の割込みIDを復帰
	cmp.b	#CL_TASK, r0h	; 多重割込みかどうか
	bne		int_return		; 多重割込みならリターン

	; 初段の割込み(タスクから)
	pop.l	er1				; タスクスタックポインタを復帰
	mov.l	er1, sp			; タスクのスタックに戻す

	; 割込み入り口（割込み禁止前）における割込み発生判定
	; スタック上のEXRの値が0であるか判定する．
	; EXRが0以外になるのは以下の2点．
	; ・割込みが発生している（多重割込み）
	; ・割込みレベルまでのリソース取得されている（ディスパッチ禁止）
	; このためEXRが0以外のときはディスパッチ判定不要
	mov.b	@(EXR_OFFSET, sp), r0l	; スタック上のEXR
	and.b	#EXR_MSK, r0l			; Tビットをマスク
	cmp.b	#0x00, r0l				; 割込み発生箇所はタスクコンテキストか
	bne		int_return				; 割込みコンテキストならリターンへ
	mov.b	@_runtsk, r0l
	mov.b	@_schedtsk, r0h
	cmp.b	r0l, r0h		;ディスパッチ要求あり？
	bne		ret_int:16		; あれば ret_int へジャンプ

int_return:
	; MACH/MACLレジスタ退避
	pop		er3
	ldmac	er3, mach
	pop		er3
	ldmac	er3, macl

	pop		er3				; レジスタ復帰
	pop		er2
	pop		er1
	pop		er0
	rte						; 割込み前の処理に戻る


;
; 未使用割込みの処理
;

	.global _unused_interrupt
_unused_interrupt:
	rte


.end

