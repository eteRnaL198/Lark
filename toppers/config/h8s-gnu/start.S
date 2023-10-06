;
;   TOPPERS Automotive Kernel
;       Toyohashi Open Platform for Embedded Real-Time Systems
;       Automotive Kernel
; 
;  Copyright (C) 2000-2004 by Embedded and Real-Time Systems Laboratory
;                              Toyohashi Univ. of Technology, JAPAN
;  Copyright (C) 2001-2004 by Dep. of Computer Science and Engineering
;                   Tomakomai National College of Technology, JAPAN
;  Copyright (C) 2001-2004 by Industrial Technology Institute,
;                              Miyagi Prefectural Government, JAPAN
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

#define _MACRO_ONLY


;
;  H8S用スタートアップモジュール
;
	.h8300s

	.section .text
	.align 2

	.global	start
	.global	hardware_init_hook
	.global	software_init_hook
	.global	_main


	.section .text
	.align 1

start:
	;
	;  タスク独立のスタックを__stack_topに初期化する
	;  （__stack_topは、リンカスクリプトで定義）
	;  ・ハードウェアマニュアル 「4.2.4 リセット直後の割込み」(P90)より
	;    プログラムの先頭命令は SP の初期化命令でなければならない。
	;
	mov.l	#__stack_top, sp

	;
	;  hardware_init_hook の呼出し（0 でない場合）
	;
	;  ターゲットハードウェアに依存して必要な初期化処理がある場合
	;  は，hardware_init_hook という関数を用意する．
	;
	mov.l	#hardware_init_hook, er0	; mov命令にてシンボルが0の場合、Z=1となる
	beq		hardware_init_hook_r
	jsr		@hardware_init_hook
hardware_init_hook_r:

	;
	; bssセクションをクリア
	;
	mov.l	#__bss_start, er0
	mov.l	#_end, er1
	sub.l	er2, er2
bbr_clear:
	mov.l	er2, @er0
	add.l	#4, er0
	cmp.l	er1, er0
	blo		bbr_clear		; er1 > er0 までジャンプ

	;
	;  dataセクションを初期化する（ROM化対応）
	;
	;  __idata_start から __idata_end までを，__data_start 以降にコピーする
	;
	mov.l	#__idata_start, er0
	mov.l	#__idata_end, er1
	mov.l	#__data_start, er2
data_init:
	mov.l	@er0+, er4		; *er2++ = *er0 ++;
	mov.l	er4, @er2
	add.l	#4, er2
	cmp.l	er1, er0
	blo		data_init		; er1 > er0 までジャンプ

	;
	;  software_init_hook を呼出し（0 でない場合）
	;
	;  ソフトウェア環境（特にライブラリ）に依存して必要な初期化処
	;  理がある場合は，software_init_hook という関数を用意すればよい．
	;
	mov.l	#software_init_hook, er0	; mov命令にてシンボルが0の場合、Z=1となる
	beq		software_init_hook_r
	jsr		@software_init_hook
software_init_hook_r:

	;
	;  ユーザメイン実行
	;
	jsr		@_main

	;
	;  EXITループ
	;
main_exit:
	jmp		main_exit

.end

