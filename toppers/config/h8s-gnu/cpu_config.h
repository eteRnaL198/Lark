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


/*
 *  プロセッサ依存モジュール（H8S用）
 */

#ifndef	_CPU_CONFIG_H_
#define	_CPU_CONFIG_H_


#ifndef _MACRO_ONLY
#include "cpu_insn.h"
#endif /* _MACRO_ONLY */

#ifndef _MACRO_ONLY

/*
 *  変数外部参照
 */
extern UINT8	saved_intpri;	/* dis_int状態での保持ipl		*/
extern UINT8	disint_flag;	/* dis_int状態管理フラグ		*/

/* インライン関数プロトタイプ宣言	*/
Inline void set_ipl(UINT8 ipl);
Inline UINT8 current_ipl(void);

/*
 *  本OSカーネルでは割込み制御をIフラグ及びIPLの双方を用いて行う
 *  ことを前提とする.このためIフラグまたはI0〜I2(IPL)のどちらかを
 *  選択するH8Sでは不足機能をソフトウェアで補う必要がある.
 *  CPUロック状態(disint_flag=TRUE)の場合はI0〜I2=7としているため,
 *  saved_intpriの値が処理対象となる.CPUアンロック状態ではI0〜I2が
 *  処理対象となる.
 */

/*
 *  割込み優先度レベル設定
 */
Inline void set_ipl(UINT8 ipl)
{
	/* CPUロック状態を判定し,処理対象にipl値を設定する.	*/
	if( TRUE == disint_flag ){
		saved_intpri = ipl;
		/* 割込み禁止中はEXRレジスタにアクセスしない	*/
	}
	else{
		Asm( "	ldc.b	%0l, exr" : : "r"(ipl) );
	}
}


/*
 *  割込み優先度レベル取得
 */
Inline UINT8 current_ipl(void)
{
	volatile UINT8	ipl;

	/* CPUロック状態を判定し,ipl値を処理対象に取得する.	*/
	if( TRUE == disint_flag ){
		ipl = saved_intpri;
	}
	else{
		Asm( "	stc.b	exr, %0l" : "=r"(ipl) );
		ipl &= 0x07;
	}

	return(ipl);
}


/*参照プロトタイプ*/
/*
 *  プロセッサ依存の初期化(cpu_config.c)
 */
extern void	cpu_initialize(void);

/*
 *  プロセッサ依存の終了時処理(cpu_config.c)
 */
extern void	cpu_terminate(void);

#define DEFINE_CTXB(tnum) \
FP tcxb_pc[tnum]; \
VP tcxb_sp[tnum];

extern FP tcxb_pc[];
extern VP tcxb_sp[];

/* ディスパッチ周りのアセンブラ関数プロトタイプ宣言	*/
extern void  dispatch(void);
extern void  exit_and_dispatch(void);
extern void  start_dispatch(void);


/*
 *  ISR1生成マクロ
 *
 *  ISR1の全ての処理をユーザが記述する場合は，cpu_defs.h にある無効化マクロ
 *  「OMIT_ISR1_ENTRY」の定義を有効にすること．
 */

/* ベクタテーブルからの外部参照宣言生成マクロ	*/
/*
 *  割込み入り口実態とベクタテーブルを別ファイルに生成する場合に必要となる．
 *  現状H8Sの全てのシステムで，同一ファイル出力となっているため本マクロは
 *  使用されたいない可能性もある．
 *  別ファイル出力を行う場合を考慮し，記載は残しておく．
 */
#if defined(OMIT_ISR1_ENTRY)
#define	ISR1_EXTERNAL(isr)		asm("	.global	_" #isr )
#else	/* OMIT_ISR1_ENTRY	*/
#define	ISR1_EXTERNAL(isr)		asm("	.global	_" #isr "_entry")
#endif	/* OMIT_ISR1_ENTRY	*/

/* ベクタテーブル登録シンボル生成マクロ	*/
#if defined(OMIT_ISR1_ENTRY)
#define	ISR1_SYMBOL(isr)		asm("	.long	_" #isr )
#else	/* OMIT_ISR1_ENTRY	*/
#define	ISR1_SYMBOL(isr)		asm("	.long	_" #isr "_entry")
#endif	/* OMIT_ISR1_ENTRY	*/

/* 入口処理の生成マクロ	*/
#if defined(OMIT_ISR1_ENTRY)
#define ISR1_ENTRY(isr)
#else	/* OMIT_ISR1_ENTRY	*/
#define ISR1_ENTRY(isr)\
asm("	.global _" #isr "				");\
asm("	.section .text					");\
asm("	.align 1						");\
asm("_" #isr "_entry:					");\
asm("	push	er0				; スクラッチレジスタをタスクスタックへ退避");\
asm("	push	er1						");\
asm("	push	er2						");\
asm("	push	er3						");\
asm("	jsr		_" #isr"				");\
asm("	pop		er3				; スクラッチレジスタをタスクスタックから復帰");\
asm("	pop		er2						");\
asm("	pop		er1						");\
asm("	pop		er0						");\
asm("	rte								");
#endif	/* OMIT_ISR1_ENTRY	*/


/*
 *  ISR2生成マクロ
 */

/* ベクタテーブルからの外部参照宣言生成マクロ	*/
/*
 *  割込み入り口実態とベクタテーブルを別ファイルに生成する場合に必要となる．
 *  現状H8Sの全てのシステムで，同一ファイル出力となっているため本マクロは
 *  使用されたいない可能性もある．
 *  別ファイル出力を行う場合を考慮し，記載は残しておく．
 */
#define	ISR2_EXTERNAL(isr)		asm("	.global	_" #isr "_entry")

/* ベクタテーブル登録シンボル生成マクロ	*/
#define	ISR2_SYMBOL(isr)		asm("	.long	_" #isr "_entry")

/*
 *  割込みハンドラの入口処理の生成マクロ
 *
 *  本割込みのIDをr0hに保持する.
 *  ユーザ割込みハンドラをer2に保持する.
 *  割込み発生時(本割込み)の優先度(I0〜I2の値)をr3lに保持する.
 *  この場合のr3lはsaved_intpriと同じ役割となる.また,disint_flagについても
 *  OS割込みハンドラ内で割込み管理を行うため設定は行わない.
 *  しかし、割込み禁止にするまでの６行の間に多重割り込みが発生した場合、
 *  多重割り込みの検出ができない。このため割込み処理ルーチンの終わりにて、
 *  saved_intpriとスタックに積まれているEXRにてタスクレベルへの復帰判定を行う。
 *
 *  レジスタ退避参考情報
 *    GCCのC関数呼び出し規約が見つからなかったため、C関数のアセンブラ
 *    展開結果から判断した情報です。
 *  ・引数：3つまではer0,er1,er2を使用(8bitデータでもer?を占有)
 *    4つめ以降はスタック渡し
 *  ・戻り値：er0を使用
 *  ・内部使用レジスタ：er0〜er3をpushせずに使用,er4/er5を必要に応じてpushして使用
 *    コンパイラは関数呼び出しをまたいでer0〜er3を使わないように展開している
 *    関数呼び出しをまたいで使う場合は呼び出し元で保持が必要
 *  ・スタック：er7(ハード仕様)
 *  ・フレームベース：er6にて実現
 *    関数の先頭で必ず呼び出し元フレームベース保持(push er6)と
 *    本関数フレームベース取得(mov.l er7, er6)が展開されている
 */
#define ISR2_ENTRY(isr, isrid)\
asm("	.global _ISRMain" #isr "			");\
asm("	.global _interrupt					");\
asm("	.section .text						");\
asm("	.align 1							");\
asm("_" #isr "_entry:						");\
asm("	push	er0						; レジスタをタスクスタックへ退避");\
asm("	push	er1							");\
asm("	push	er2							");\
asm("	push	er3							");\
asm("	stc.b	exr, r3l				; 発生割込み優先度を保持");\
asm("	ldc.b	#0x07, exr				; 割込み禁止");\
asm("	mov.l	#_ISRMain" #isr ", er2	; 割込みハンドラのアドレスをer2へ");\
asm("	mov.b	#" #isrid ", r0h		; 発生した割込みのIDを");\
asm("	jmp		_interrupt				; 割込み処理ルーチン後半へ");


/*
 *  未使用割込み生成マクロ
 */

/* ベクタテーブルからの外部参照宣言生成マクロ	*/
#define	UNUSED_INT_EXTERNAL()	asm("	.global	_unused_interrupt")

/* ベクタテーブル登録シンボル生成マクロ	*/
#define	UNUSED_INT_SYMBOL()		asm("	.long	_unused_interrupt")


/*
 *  フックルーチンNULLシンボル生成マクロ
 */
#define	NULL_ERRORHOOK \
asm(".global	_ErrorHook");\
asm(".equ _ErrorHook,		0");

#define	NULL_STARTUPHOOK \
asm(".global	_StartupHook"); \
asm(".equ _StartupHook,		0");

#define	NULL_SHUTDOWNHOOK \
asm(".global	_ShutdownHook"); \
asm(".equ _ShutdownHook,	0");

#define	NULL_PRETASKHOOK \
asm(".global	_PreTaskHook"); \
asm(".equ _PreTaskHook,		0");

#define	NULL_POSTTASKHOOK \
asm(".global	_PostTaskHook"); \
asm(".equ _PostTaskHook,	0");


#endif /* _MACRO_ONLY */
#endif	/* _CPU_CONFIG_H_	*/

