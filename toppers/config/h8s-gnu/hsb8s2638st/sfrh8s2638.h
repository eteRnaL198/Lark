/*
 *  TOPPERS Automotive Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel
 * 
 *  Copyright (C) 2006 by Witz Corporation, JAPAN
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
 *  SFRヘッダファイル(H8S/2638用)
 */
#if !defined( _SFR_H8S2638_H_ )				/* 二重定義防止					*/
#define		_SFR_H8S2638_H_					/* 二重定義防止					*/


#if defined( USE_EXT_RAM )
/*
 *  拡張メモリアドレスファイルインクルード
 */
#include "ext_mem_addr.h"
#endif	/* defined(USE_EXT_RAM) */


/*
 *  H8S ルネサスコンパイラではビットフィールド定義は
 *  定義した順番にbit7, 6, 5, ...という順番に定義されるため、
 *  要注意
 */

/********************************************************/
/*  MCU動作モード										*/
/********************************************************/
/*
 *  モードコントロールレジスタ
 */
#define		mdcr_addr		(*(volatile UINT8	*)0xFFFDE7)

#define		MDCR			mdcr_addr

/*
 *  システムコントロールレジスタ
 */
#define		syscr_addr		(*(volatile UINT8	*)0xFFFDE5)

#define		SYSCR			syscr_addr

/*
 *  端子機能コントロールレジスタ
 */
#define		pfcr_addr		(*(volatile UINT8	*)0xFFFDEB)

#define		PFCR			pfcr_addr


/********************************************************/
/* 割込みコントローラー									*/
/********************************************************/
/*
 *  IRQ センスコントロールレジスタ
 */
typedef union {
	struct {
		UINT8	iscr_high;	/* RW IRQ 上位8bit								*/
		UINT8	iscr_low;	/* RW IRQ 下位8bit								*/
	} byte;
	UINT16	word;			/* RW IRQ 32bit									*/
} ISCR_TYPE;

#define		iscr_addr		(*(volatile ISCR_TYPE	*)0xFFFE12)

#define		ISCR			iscr_addr.word
#define		ISCRH			iscr_addr.byte.iscr_high
#define		ISCRL			iscr_addr.byte.iscr_low

/*
 *  IRQ イネーブルレジスタ
 */
#define		ier_addr		(*(volatile UINT8	*)0xFFFE14)

#define		IER				ier_addr

/*
 *  IRQ ステータスレジスタ
 */
#define		istr_addr		(*(volatile UINT8	*)0xFFFE15)

#define		ISTR			istr_addr

/*
 *  インタラプトプライオリティレジスタA
 */
#define		ipra_addr		(*(volatile UINT8	*)0xFFFEC0)

#define		IPRA			ipra_addr

/*
 *  インタラプトプライオリティレジスタB
 */
#define		iprb_addr		(*(volatile UINT8	*)0xFFFEC1)

#define		IPRB			iprb_addr

/*
 *  インタラプトプライオリティレジスタC
 */
#define		iprc_addr		(*(volatile UINT8	*)0xFFFEC2)

#define		IPRC			iprc_addr

/*
 *  インタラプトプライオリティレジスタD
 */
#define		iprd_addr		(*(volatile UINT8	*)0xFFFEC3)

#define		IPRD			iprd_addr

/*
 *  インタラプトプライオリティレジスタE
 */
#define		ipre_addr		(*(volatile UINT8	*)0xFFFEC4)

#define		IPRE			ipre_addr

/*
 *  インタラプトプライオリティレジスタF
 */
#define		iprf_addr		(*(volatile UINT8	*)0xFFFEC5)

#define		IPRF			iprf_addr

/*
 *  インタラプトプライオリティレジスタG
 */
#define		iprg_addr		(*(volatile UINT8	*)0xFFFEC6)

#define		IPRG			iprg_addr

/*
 *  インタラプトプライオリティレジスタH
 */
#define		iprh_addr		(*(volatile UINT8	*)0xFFFEC7)

#define		IPRH			iprh_addr

/*
 *  インタラプトプライオリティレジスタJ
 */
#define		iprj_addr		(*(volatile UINT8	*)0xFFFEC9)

#define		IPRJ			iprj_addr

/*
 *  インタラプトプライオリティレジスタK
 */
#define		iprk_addr		(*(volatile UINT8	*)0xFFFECA)

#define		IPRK			iprk_addr

/*
 *  インタラプトプライオリティレジスタL
 */
#define		iprl_addr		(*(volatile UINT8	*)0xFFFECB)

#define		IPRL			iprl_addr

/*
 *  インタラプトプライオリティレジスタM
 */
#define		iprm_addr		(*(volatile UINT8	*)0xFFFECC)

#define		IPRM			iprm_addr


/********************************************************/
/*  PCブレークコントローラ								*/
/********************************************************/
/*
 *  ブレークアドレスレジスタA
 */
#define		bara_addr		(*(volatile UINT32	*)0xFFFE00)

#define		BARA			bara_addr

/*
 *  ブレークアドレスレジスタB
 */
#define		barb_addr		(*(volatile UINT32	*)0xFFFE04)

#define		BARB			barb_addr

/*
 *  ブレークコントロールレジスタA
 */
#define		brkcra_addr		(*(volatile UINT8	*)0xFFFE08)

#define		BRKCRA			brkcra_addr

/*
 *  ブレークコントロールレジスタB
 */
#define		brkcrb_addr		(*(volatile UINT8	*)0xFFFE09)

#define		BRKCRB			brkcrb_addr

/*
 *  モジュールストップコントロールレジスタC
 */
#define		mstpcrc_addr	(*(volatile UINT8	*)0xFFFDEA)

#define		MSTPCRC			mstpcrc_addr


/********************************************************/
/*  バスコントローラ									*/
/********************************************************/
/*
 *  バス幅コントロールレジスタ
 */
#define		abwcr_addr		(*(volatile UINT8	*)0xFFFED0)

#define		ABWCR			abwcr_addr

/*
 *  アクセスステートコントロールレジスタ
 */
#define		astcr_addr		(*(volatile UINT8	*)0xFFFED1)

#define		ASTCR			astcr_addr

/*
 *  ウェイトコントロールレジスタH
 */
#define		wcrh_addr		(*(volatile UINT8	*)0xFFFED2)

#define		WCRH			wcrh_addr

/*
 *  ウェイトコントロールレジスタL
 */
#define		wcrl_addr		(*(volatile UINT8	*)0xFFFED3)

#define		WCRL			wcrl_addr

/*
 *  バスコントロールレジスタH
 */
#define		buscrh_addr		(*(volatile UINT8	*)0xFFFED4)

#define		BUSCRH			buscrh_addr

/*
 *  バスコントロールレジスタL
 */
#define		buscrl_addr		(*(volatile UINT8	*)0xFFFED5)
 
#define		BUSCRL			buscrl_addr


/********************************************************/
/*  データトランスファコントローラ						*/
/********************************************************/
/*
 *  DTCモードレジスタA,B
 */
/*
 *  ※このレジスタはR/W不可
 */

/*
 *  DTCソースアドレスレジスタ
 */
/*
 *  ※このレジスタはR/W不可
 */

/*
 *  DTCデスティネーションアドレスレジスタ
 */
/*
 *  ※このレジスタはR/W不可
 */

/*
 *  DTC転送カウントレジスタA,B
 */
/*
 *  ※このレジスタはR/W不可
 */

/*
 *  DTCイネーブルレジスタA
 */
#define		dtcera_addr		(*(volatile UINT8	*)0xFFFE16)

#define		DTCERA			dtcera_addr

/*
 *  DTCイネーブルレジスタB
 */
#define		dtcerb_addr		(*(volatile UINT8	*)0xFFFE17)

#define		DTCERB			dtcerb_addr

/*
 *  DTCイネーブルレジスタC
 */
#define		dtcerc_addr		(*(volatile UINT8	*)0xFFFE18)

#define		DTCERC			dtcerc_addr

/*
 *  DTCイネーブルレジスタD
 */
#define		dtcerd_addr		(*(volatile UINT8	*)0xFFFE19)

#define		DTCERD			dtcerd_addr

/*
 *  DTCイネーブルレジスタE
 */
#define		dtcere_addr		(*(volatile UINT8	*)0xFFFE1A)

#define		DTCERE			dtcere_addr

/*
 *  DTCイネーブルレジスタF
 */
#define		dtcerf_addr		(*(volatile UINT8	*)0xFFFE1B)

#define		DTCERF			dtcerf_addr

/*
 *  DTCイネーブルレジスタG
 */
#define		dtcerg_addr		(*(volatile UINT8	*)0xFFFE1C)

#define		DTCERG			dtcerg_addr

/*
 *  DTCベクタレジスタ
 */
#define		dtvecr_addr		(*(volatile UINT8	*)0xFFFE1F)

#define		DTVECR			dtvecr_addr

/*
 *  モジュールストップコントロールレジスタA
 */
#define		mstpcra_addr	(*(volatile UINT8	*)0xFFFDE8)

#define		MSTPCRA			mstpcra_addr


/********************************************************/
/* I/Oポート											*/
/********************************************************/
/*
 *  ポート1 データディレクションレジスタ
 */
#define		p1ddr_addr		(*(volatile UINT8	*)0xFFFE30)

#define		P1DDR			p1ddr_addr


/*
 *  ポート1 データレジスタ
 */
#define		p1dr_addr		(*(volatile UINT8	*)0xFFFF00)

#define		P1DR			p1dr_addr

/*
 *  ポート1 レジスタ
 */
#define		port1_addr		(*(volatile UINT8	*)0xFFFFB0)

#define		PORT1			port1_addr

/*
 *  ポート3 データディレクションレジスタ
 */
#define		p3ddr_addr		(*(volatile UINT8	*)0xFFFE32)

#define		P3DDR			p3ddr_addr

/*
 *  ポート3 データレジスタ
 */
#define		p3dr_addr		(*(volatile UINT8	*)0xFFFF02)

#define		P3DR			p3dr_addr

/*
 *  ポート3 レジスタ
 */
#define		port3_addr		(*(volatile UINT8	*)0xFFFFB2)

#define		PORT3			port3_addr

/*
 *   ポート3 オープンドレインコントロールレジスタ
 */
#define		p3odr_addr		(*(volatile UINT8	*)0xFFFE46)

#define		P3ODR			p3odr_addr

/*
 *   ポート4 レジスタ
 */
#define		port4_addr		(*(volatile UINT8	*)0xFFFFB3)

#define		PORT4			port4_addr

/*
 *ポート9 レジスタ
 */
#define		port9_addr		(*(volatile UINT8	*)0xFFFFB8)

#define		PORT9			port9_addr

/*
 *	ポートA データディレクションレジスタ
 */
#define		paddr_addr		(*(volatile UINT8	*)0xFFFE39)

#define		PADDR			paddr_addr

/*
 *  ポートAデータレジスタ
 */
#define		padr_addr		(*(volatile UINT8	*)0xFFFF09)

#define		PADR			padr_addr

/*
 *  ポートAレジスタ
 */
#define		porta_addr		(*(volatile UINT8	*)0xFFFFB9)

#define		PORTA			porta_addr

/*
 *  ポートAプルアップMOSコントロールレジスタ
 */
#define		papcr_addr		(*(volatile UINT8	*)0xFFFE40)

#define		PAPCR			papcr_addr

/*
 *  ポートAオープンドレインコントロールレジスタ
 */
#define		paodr_addr		(*(volatile UINT8	*)0xFFFE47)

#define		PAODR			paodr_addr

/*
 *  ポートBデータディレクションレジスタ
 */
#define		pbddr_addr		(*(volatile UINT8	*)0xFFFE3A)

#define		PBDDR			pbddr_addr

/*
 *  ポートBデータレジスタ
 */
#define		pbdr_addr		(*(volatile UINT8	*)0xFFFF0A)

#define		PBDR			pbdr_addr

/*
 *  ポートBレジスタ
 */
#define		portb_addr		(*(volatile UINT8	*)0xFFFFBA)

#define		PORTB			portb_addr

/*
 *  ポートBプルアップMOSコントロールレジスタ
 */
#define		pbpcr_addr		(*(volatile UINT8	*)0xFFFE41)

#define		PBPCR			pbpcr_addr

/*
 *  ポートBオープンドレインコントロールレジスタ
 */
#define		pbodr_addr		(*(volatile UINT8	*)0xFFFE48)

#define		PBODR			pbodr_addr

/*
 *  ポートCデータディレクションレジスタ
 */
#define		pcddr_addr		(*(volatile UINT8	*)0xFFFE3B)

#define		PCDDR			pcddr_addr

/*
 *  ポートCデータレジスタ
 */
#define		pcdr_addr		(*(volatile UINT8	*)0xFFFF0B)

#define		PCDR			pcdr_addr

/*
 *  ポートCレジスタ
 */
#define		portc_addr		(*(volatile UINT8	*)0xFFFFBB)

#define		PORTC			portc_addr

/*
 *  ポートCプルアップMOSコントロールレジスタ
 */
#define		pcpcr_addr		(*(volatile UINT8	*)0xFFFE42)

#define		PCPCR			pcpcr_addr

/*
 *  ポートCオープンドレインコントロールレジスタ
 */
#define		pcodr_addr		(*(volatile UINT8	*)0xFFFE49)

#define		PCODR			pcodr_addr

/*
 *  ポートDデータディレクションレジスタ
 */
#define		pdddr_addr		(*(volatile UINT8	*)0xFFFE3C)

#define		PDDDR			pdddr_addr

/*
 *  ポートDデータレジスタ
 */
#define		pddr_addr		(*(volatile UINT8	*)0xFFFF0C)

#define		PDDR			pddr_addr

/*
 *  ポートDレジスタ
 */
#define		portd_addr		(*(volatile UINT8	*)0xFFFFBC)

#define		PORTD			portd_addr

/*
 *  ポートDプルアップMOSコントロールレジスタ
 */
#define		pdpcr_addr		(*(volatile UINT8	*)0xFFFE43)

#define		PDPCR			pdpcr_addr

/*
 *  ポートEデータディレクションレジスタ
 */
#define		peddr_addr		(*(volatile UINT8	*)0xFFFE3D)

#define		PEDDR			peddr_addr

/*
 *  ポートEデータレジスタ
 */
#define		pedr_addr		(*(volatile UINT8	*)0xFFFF0D)

#define		PEDR			pedr_addr

/*
 *  ポートEレジスタ
 */
#define		porte_addr		(*(volatile UINT8	*)0xFFFFBD)

#define		PORTE			porte_addr

/*
 *  ポートEプルアップMOSコントロールレジスタ
 */

#define		pepcr_addr		(*(volatile UINT8	*)0xFFFE44)

#define		PEPCR			pepcr_addr

/*
 *  ポートF データディレクションレジスタ
 */
#define		pfddr_addr		(*(volatile UINT8	*)0xFFFE3E)

#define		PFDDR			pfddr_addr

/*
 *  ポートF データレジスタ
 */
#define		pfdr_addr		(*(volatile UINT8	*)0xFFFF0E)

#define		PFDR			pfdr_addr

/*
 *  ポートF レジスタ
 */
#define		portf_addr		(*(volatile UINT8	*)0xFFFFBE)

#define		PORTF			portf_addr

/*
 *  ポートHデータディレクションレジスタ
 */
#define		phddr_addr		(*(volatile UINT8	*)0xFFFC20)

#define		PHDDR			phddr_addr

/*
 *  ポートHデータレジスタ
 */
#define		phdr_addr		(*(volatile UINT8	*)0xFFFC24)

#define		PHDR			phdr_addr

/*
 *  ポートHレジスタ
 */
#define		porth_addr		(*(volatile UINT8	*)0xFFFC28)

#define		PORTH			porth_addr

/*
 *  ポートJデータディレクションレジスタ
 */
#define		pjddr_addr		(*(volatile UINT8	*)0xFFFC21)

#define		PJDDR			pjddr_addr

/*
 *  ポートJデータレジスタ
 */
#define		pjdr_addr		(*(volatile UINT8	*)0xFFFC25)

#define		PJDR			pjdr_addr

/*
 *  ポートJレジスタ
 */
#define		portj_addr		(*(volatile UINT8	*)0xFFFC29)

#define		PORTJ			portj_addr


/********************************************************/
/*  16ビットタイマパルスユニット						*/
/********************************************************/
/*
 *  タイマコントロールレジスタ0
 */
#define		tcr0_addr		(*(volatile UINT8	*)0xFFFF10)

#define		TCR0			tcr0_addr

/*
 *  タイマコントロールレジスタ3
 */
#define		tcr3_addr		(*(volatile UINT8	*)0xFFFE80)

#define		TCR3			tcr3_addr


/*
 *  タイマコントロールレジスタ1
 */
#define		tcr1_addr		(*(volatile UINT8	*)0xFFFF20)

#define		TCR1			tcr1_addr

/*
 *  タイマコントロールレジスタ2
 */
#define		tcr2_addr		(*(volatile UINT8	*)0xFFFF30)

#define		TCR2			tcr2_addr

/*
 *  タイマコントロールレジスタ4
 */
#define		tcr4_addr		(*(volatile UINT8	*)0xFFFE90)

#define		TCR4			tcr4_addr

/*
 *  タイマコントロールレジスタ5
 */
#define		tcr5_addr		(*(volatile UINT8	*)0xFFFEA0)

#define		TCR5			tcr5_addr
 
/*
 *  タイマモードレジスタ0
 */
#define		tmdr0_addr		(*(volatile UINT8	*)0xFFFF11)

#define		TMDR0			tmdr0_addr

/*
 *  タイマモードレジスタ3
 */
#define		tmdr3_addr		(*(volatile UINT8	*)0xFFFE81)

#define		TMDR3			tmdr3_addr


/*
 *  タイマモードレジスタ1
 */
#define		tmdr1_addr		(*(volatile UINT8	*)0xFFFF21)

#define		TMDR1			tmdr1_addr

/*
 *  タイマモードレジスタ2
 */
#define		tmdr2_addr		(*(volatile UINT8	*)0xFFFF31)

#define		TMDR2			tmdr2_addr

/*
 *  タイマモードレジスタ4
 */
#define		tmdr4_addr		(*(volatile UINT8	*)0xFFFE91)

#define		TMDR4			tmdr4_addr

/*
 *  タイマモードレジスタ5
 */
#define		tmdr5_addr		(*(volatile UINT8	*)0xFFFEA1)

#define		TMDR5			tmdr5_addr

/*
 *  タイマI/O コントロールレジスタ0 H
 */
#define		tior0h_addr		(*(volatile UINT8	*)0xFFFF12)

#define		TIOR0H			tior0h_addr

/*
 *  タイマI/O コントロールレジスタ1
 */
#define		tior1_addr		(*(volatile UINT8	*)0xFFFF22)

#define		TIOR1			tior1_addr

/*
 *  タイマI/O コントロールレジスタ2
 */
#define		tior2_addr		(*(volatile UINT8	*)0xFFFF32)

#define		TIOR2			tior2_addr

/*
 *  タイマI/O コントロールレジスタ3 H
 */
#define		tior3h_addr		(*(volatile UINT8	*)0xFFFE82)

#define		TIOR3H			tior3h_addr

/*
 *  タイマI/O コントロールレジスタ4
 */
#define		tior4_addr		(*(volatile UINT8	*)0xFFFE92)

#define		TIOR4			tior4_addr

/*
 *  タイマI/O コントロールレジスタ5
 */
#define		tior5_addr		(*(volatile UINT8	*)0xFFFEA2)

#define		TIOR5			tior5_addr

/*
 *  タイマI/O コントロールレジスタ0 L
 */
#define		tior0l_addr		(*(volatile UINT8	*)0xFFFF13)

#define		TIOR0L			tior0l_addr

/*
 *  タイマI/O コントロールレジスタ3 L
 */
#define		tior3l_addr		(*(volatile UINT8	*)0xFFFE83)

#define		TIOR3L			tior3l_addr

/*
 *  タイマインタラプトイネーブルレジスタ0
 */
#define		tier0_addr		(*(volatile UINT8	*)0xFFFF14)

#define		TIER0			tier0_addr

/*
 *  タイマインタラプトイネーブルレジスタ3
 */
#define		tier3_addr		(*(volatile UINT8	*)0xFFFE84)

#define		TIER3			tier3_addr

/*
 *  タイマインタラプトイネーブルレジスタ１
 */
#define		tier1_addr		(*(volatile UINT8	*)0xFFFF24)

#define		TIER1			tier1_addr

/*
 *  タイマインタラプトイネーブルレジスタ2
 */
#define		tier2_addr		(*(volatile UINT8	*)0xFFFF34)

#define		TIER2			tier2_addr
 
/*
 *  タイマインタラプトイネーブルレジスタ4
 */
#define		tier4_addr		(*(volatile UINT8	*)0xFFFE94)

#define		TIER4			tier4_addr
 
/*
 *  タイマインタラプトイネーブルレジスタ5
 */
#define		tier5_addr		(*(volatile UINT8	*)0xFFFEA4)

#define		TIER5			tier5_addr

/*
 *  タイマステータスレジスタ0
 */
#define		tsr0_addr		(*(volatile UINT8	*)0xFFFF15)

#define		TSR0			tsr0_addr

/*
 *  タイマステータスレジスタ3
 */
#define		tsr3_addr		(*(volatile UINT8	*)0xFFFE85)

#define		TSR3			tsr3_addr

/*
 *  タイマステータスレジスタ1
 */
#define		tsr1_addr		(*(volatile UINT8	*)0xFFFF25)

#define		TSR1			tsr1_addr

/*
 *  タイマステータスレジスタ2
 */
#define		tsr2_addr		(*(volatile UINT8	*)0xFFFF35)

#define		TSR2			tsr2_addr

/*
 *  タイマステータスレジスタ4
 */
#define		tsr4_addr		(*(volatile UINT8	*)0xFFFE95)

#define		TSR4			tsr4_addr
 
/*
 *  タイマステータスレジスタ5
 */
#define		tsr5_addr		(*(volatile UINT8	*)0xFFFEA5)

#define		TSR5			tsr5_addr

/*
 *  タイマカウンタ0
 */
#define		tcnt0_addr		(*(volatile UINT16		*)0xFFFF16)

#define		TCNT0			tcnt0_addr

/*
 *  タイマカウンタ1
 */
#define		tcnt1_addr		(*(volatile UINT16		*)0xFFFF26)

#define		TCNT1			tcnt1_addr

/*
 *  タイマカウンタ2
 */
#define		tcnt2_addr		(*(volatile UINT16		*)0xFFFF36)

#define		TCNT2			tcnt2_addr

/*
 *  タイマカウンタ3
 */
#define		tcnt3_addr		(*(volatile UINT16		*)0xFFFE86)

#define		TCNT3			tcnt3_addr

/*
 *  タイマカウンタ4
 */
#define		tcnt4_addr		(*(volatile UINT16		*)0xFFFE96)

#define		TCNT4			tcnt4_addr

/*
 *  タイマカウンタ5
 */
#define		tcnt5_addr		(*(volatile UINT16		*)0xFFFEA6)

#define		TCNT5			tcnt5_addr

/*
 *  タイマジェネラルレジスタ0A
 */
#define		tgr0a_addr		(*(volatile UINT16		*)0xFFFF18)

#define		TGR0A			tgr0a_addr

/*
 *  タイマジェネラルレジスタ1A
 */
#define		tgr1a_addr		(*(volatile UINT16		*)0xFFFF28)

#define		TGR1A			tgr1a_addr

/*
 *  タイマジェネラルレジスタ2A
 */
#define		tgr2a_addr		(*(volatile UINT16		*)0xFFFF38)

#define		TGR2A			tgr2a_addr

/*
 *  タイマジェネラルレジスタ3A
 */
#define		tgr3a_addr		(*(volatile UINT16		*)0xFFFE88)

#define		TGR3A			tgr3a_addr

/*
 *  タイマジェネラルレジスタ4A
 */
#define		tgr4a_addr		(*(volatile UINT16		*)0xFFFE98)

#define		TGR4A			tgr4a_addr

/*
 *  タイマジェネラルレジスタ5A
 */
#define		tgr5a_addr		(*(volatile UINT16		*)0xFFFEA8)

#define		TGR5A			tgr5a_addr
/*
 *  タイマジェネラルレジスタ0B
 */
#define		tgr0b_addr		(*(volatile UINT16		*)0xFFFF1A)

#define		TGR0B			tgr0b_addr

/*
 *  タイマジェネラルレジスタ1B
 */
#define		tgr1b_addr		(*(volatile UINT16		*)0xFFFF2A)

#define		TGR1B			tgr1b_addr

/*
 *  タイマジェネラルレジスタ2B
 */
#define		tgr2b_addr		(*(volatile UINT16		*)0xFFFF3A)

#define		TGR2B			tgr2b_addr

/*
 *  タイマジェネラルレジスタ3B
 */
#define		tgr3b_addr		(*(volatile UINT16		*)0xFFFE8A)

#define		TGR3B			tgr3b_addr

/*
 *  タイマジェネラルレジスタ4B
 */
#define		tgr4b_addr		(*(volatile UINT16		*)0xFFFE9A)

#define		TGR4B			tgr4b_addr

/*
 *  タイマジェネラルレジスタ5B
 */
#define		tgr5b_addr		(*(volatile UINT16		*)0xFFFEAA)

#define		TGR5B			tgr5b_addr
/*
 *  タイマジェネラルレジスタ0C
 */
#define		tgr0c_addr		(*(volatile UINT16		*)0xFFFF1C)

#define		TGR0C			tgr0c_addr

/*
 *  タイマジェネラルレジスタ3C
 */
#define		tgr3c_addr		(*(volatile UINT16		*)0xFFFE8C)

#define		TGR3C			tgr3c_addr

/*
 *  タイマジェネラルレジスタ0D
 */
#define		tgr0d_addr		(*(volatile UINT16		*)0xFFFF1E)

#define		TGR0D			tgr0d_addr

/*
 *  タイマジェネラルレジスタ3D
 */
#define		tgr3d_addr		(*(volatile UINT16		*)0xFFFE8E)

#define		TGR3D			tgr3d_addr

/*
 *  タイマスタートレジスタ
 */
#define		tstr_addr		(*(volatile UINT8		*)0xFFFEB0)

#define		TSTR			tstr_addr

/*
 *  タイマシンクロレジスタ
 */
#define		tsyr_addr		(*(volatile UINT8		*)0xFFFEB1)

#define		TSYR			tsyr_addr


/********************************************************/
/*  プログラマブルパルスジェネレータ					*/
/********************************************************/
/*
 *  ネクストデータイネーブルレジスタ
 */
typedef union {
	struct {
		UINT8	nder_high;
		UINT8	nder_low;
	} byte;
	UINT16		word;
} NDER_TYPE;

#define		nder_addr		(*(volatile NDER_TYPE	*)0xFFFE28)

#define		NDER			nder_addr.word
#define		NDERH			nder_addr.byte.nder_high
#define		NDERL			nder_addr.byte.nder_low

/*
 *  アウトプットデータレジスタ H
 */
 typedef union {
	struct {
		UINT8	podr_high;
		UINT8	podr_low;
	} byte;
 	UINT16		word;
 } PODR_TYPE;

#define		podr_addr		(*(volatile PODR_TYPE	*)0xFFFE2A)

#define		PODR			podr_addr.word
#define		PODRH			podr_addr.byte.podr_high
#define		PODRL			podr_addr.byte.podr_low

/*
 *  ネクストデータレジスタH A
 */
#define		ndrha_addr		(*(volatile UINT8	*)0xFFFE2C)

#define		NDRHA			ndrha_addr

/*
 *  ネクストデータレジスタH B
 */
#define		ndrhb_addr		(*(volatile UINT8	*)0xFFFE2E)

#define		NDRHB			ndrhb_addr

/*
 *  ネクストデータレジスタL C
 */
#define		ndrlc_addr		(*(volatile UINT8	*)0xFFFE2D)

#define		NDRLC			ndrlc_addr

/*
 *  ネクストデータレジスタL D
 */
#define		ndrld_addr		(*(volatile UINT8	*)0xFFFE2F)

#define		NDRLD			ndrld_addr

/*
 *  PPG出力コントロールレジスタ
 */
#define		pcr_addr		(*(volatile UINT8	*)0xFFFE26)

#define		PCR				pcr_addr

/*
 *  PPG出力モードレジスタ
 */
#define		pmr_addr		(*(volatile UINT8	*)0xFFFE27)

#define		PMR				pmr_addr


/********************************************************/
/*  ウォッチドッグタイマ								*/
/********************************************************/
/*
 *  タイマコントロール/ステータスレジスタ
 */
/*
 *  ※レジスタへのアクセス方法はハードウェアマニュアル参照
 */
typedef union {
	struct {
		UINT8	tcsr_low;	/* RW TCSR0/1レジスタ							*/
		UINT8	tcsr_high;	/* RW TCSRへライトする場合はH'A5を書込むこと	*/
	} byte;
	UINT16		word;
} TCSR_TYPE;

/*
 *  タイマコントロール/ステータスレジスタ0
 */
#define		tcsr0_addr		(*(volatile TCSR_TYPE	*)0xFFFF74)

#define		TCSR0			tcsr0_addr.word
#define		TCSR0H			tcsr0_addr.byte.tcsr_high
#define		TCSR0L			tcsr0_addr.byte.tcsr_low

/*
 *  タイマコントロール/ステータスレジスタ1
 */
#define		tcsr1_addr		(*(volatile TCSR_TYPE	*)0xFFFFA2)
 
#define		TCSR1			tcsr1_addr.word
#define		TCSR1H			tcsr1_addr.byte.tcsr_high
#define		TCSR1L			tcsr1_addr.byte.tcsr_low

/*
 *  タイマカウンタ
 */
/*
 *  ※レジスタへのアクセス方法はハードウェアマニュアル参照
 */
typedef union {
	struct {
		UINT8	tcnt_low;	/* RW タイマカウンタ値							*/
		UINT8	tcnt_high;	/* RW TCNTへライトする場合はH'5Aを書込むこと	*/
							/*    TCNTからリードする場合は上位バイトを読み出すこと*/
	} byte;
	UINT16		word;
} WDT_TCNT_TYPE;

/*
 *  タイマカウンタ0
 */
#define		wdt_tcnt0_addr	(*(volatile WDT_TCNT_TYPE	*)0xFFFF74)

#define		WDT_TCNT0		wdt_tcnt0_addr.word
#define		WDT_TCNT0H		wdt_tcnt0_addr.byte.tcnt_high
#define		WDT_TCNT0L		wdt_tcnt0_addr.byte.tcnt_low

/*
 *  タイマカウンタ1
 */
#define		wdt_tcnt1_addr	(*(volatile WDT_TCNT_TYPE	*)0xFFFFA2)

#define		WDT_TCNT1		wdt_tcnt1_addr.word
#define		WDT_TCNT1H		wdt_tcnt1_addr.byte.tcnt_high
#define		WDT_TCNT1L		wdt_tcnt1_addr.byte.tcnt_low

/*
 *  リセットコントロール/ステータスレジスタ
 */
/*
 *  ※レジスタへのアクセス方法はハードウェアマニュアル参照
 */
typedef union {
	struct {
		UINT8	rstcsr_low;	/* RW RSTCSRへのライトデータ					*/
		UINT8	rstcsr_high;/* RW WOVFビットへ0ライトする場合はH'A5を書込むこと*/
							/*    RSTE、RSTSビットへライトする場合はH'5Aを書込むこと*/
							/*    RSTCSRからリードする場合は上位バイトを読み出すこと*/
	} byte;
	UINT16		word;
} RSTCSR_TYPE;

#define		rstcsr_addr		(*(volatile RSTCSR_TYPE	*)0xFFFF76)

#define		RSTCSR			rstcsr_addr.word
#define		RSTCSRH			rstcsr_addr.byte.rstcsr_high
#define		RSTCSRL			rstcsr_addr.byte.rstcsr_low


/********************************************************/
/*  シリアルコミュニケーションインタフェース			*/
/********************************************************/
/*
 *  シリアルモードレジスタ0
 */
#define		smr0_addr		(*(volatile UINT8	*)0xFFFF78)

#define		SMR0			smr0_addr

/*
 *  シリアルモードレジスタ1
 */
#define		smr1_addr		(*(volatile UINT8	*)0xFFFF80)

#define		SMR1			smr1_addr

/*
 *  シリアルモードレジスタ2
 */
#define		smr2_addr		(*(volatile UINT8	*)0xFFFF88)

#define		SMR2			smr2_addr

/*
 *  ビットレートレジスタ0
 */
#define		brr0_addr		(*(volatile UINT8		*)0xFFFF79)

#define		BRR0			brr0_addr

/*
 *  ビットレートレジスタ1
 */
#define		brr1_addr		(*(volatile UINT8		*)0xFFFF81)

#define		BRR1			brr1_addr

/*
 *  ビットレートレジスタ2
 */
#define		brr2_addr		(*(volatile UINT8		*)0xFFFF89)

#define		BRR2			brr2_addr

/*
 *  シリアルコントロールレジスタ0
 */
#define		scr0_addr		(*(volatile UINT8		*)0xFFFF7A)

#define		SCR0			scr0_addr

/*
 *  シリアルコントロールレジスタ1
 */
#define		scr1_addr		(*(volatile UINT8		*)0xFFFF82)

#define		SCR1			scr1_addr

/*
 *  シリアルコントロールレジスタ2
 */
#define		scr2_addr		(*(volatile UINT8		*)0xFFFF8A)

#define		SCR2			scr2_addr

/*
 *  トランスミットデータレジスタ0
 */
#define		tdr0_addr		(*(volatile UINT8		*)0xFFFF7B)

#define		TDR0			tdr0_addr

/*
 *  トランスミットデータレジスタ1
 */
#define		tdr1_addr		(*(volatile UINT8		*)0xFFFF83)

#define		TDR1			tdr1_addr

/*
 *  トランスミットデータレジスタ2
 */
#define		tdr2_addr		(*(volatile UINT8		*)0xFFFF8B)

#define		TDR2			tdr2_addr

/*
 *  シリアルステータスレジスタ0
 */
#define		ssr0_addr		(*(volatile UINT8		*)0xFFFF7C)

#define		SSR0			ssr0_addr

/*
 *  シリアルステータスレジスタ1
 */
#define		ssr1_addr		(*(volatile UINT8		*)0xFFFF84)

#define		SSR1			ssr1_addr

/*
 *  シリアルステータスレジスタ2
 */
#define		ssr2_addr		(*(volatile UINT8		*)0xFFFF8C)

#define		SSR2			ssr2_addr

/*
 *  レシーブシフトレジスタ0
 */
#define		rdr0_addr		(*(volatile UINT8		*)0xFFFF7D)

#define		RDR0			rdr0_addr

/*
 *  レシーブシフトレジスタ1
 */
#define		rdr1_addr		(*(volatile UINT8		*)0xFFFF85)

#define		RDR1			rdr1_addr

/*
 *  レシーブシフトレジスタ2
 */
#define		rdr2_addr		(*(volatile UINT8		*)0xFFFF8D)

#define		RDR2			rdr2_addr

/*
 *  スマートカードモードレジスタ0
 */
#define		scmr0_addr		(*(volatile UINT8		*)0xFFFF7E)

#define		SCMR0			scmr0_addr

/*
 *  スマートカードモードレジスタ1
 */
#define		scmr1_addr		(*(volatile UINT8		*)0xFFFF86)

#define		SCMR1			scmr1_addr

/*
 *  スマートカードモードレジスタ2
 */
#define		scmr2_addr		(*(volatile UINT8		*)0xFFFF8E)

#define		SCMR2			scmr2_addr

/*
 *  モジュールストップコントロールレジスタB
 */
#define		mstpcrb_addr	(*(volatile UINT8		*)0xFFFDE9)

#define		MSTPCRB			mstpcrb_addr


/********************************************************/
/*  I2Cバスインタフェース								*/
/********************************************************/
/*
 *  I2Cバスデータレジスタ0
 */
#define		icdr0_addr		(*(volatile UINT8		*)0xFFFF7E)

#define		ICDR0			icdr0_addr

/*
 *  I2Cバスデータレジスタ1
 */
#define		icdr1_addr		(*(volatile UINT8		*)0xFFFF86)

#define		ICDR1			icdr1_addr

/*
 *  スレーブアドレスレジスタ0
 */
#define		sar0_addr		(*(volatile UINT8		*)0xFFFF7F)

#define		SAR0			sar0_addr
 
/*
 *  スレーブアドレスレジスタ1
 */
#define		sar1_addr		(*(volatile UINT8		*)0xFFFF87)

#define		SAR1			sar1_addr

/*
 *  第2スレーブアドレスレジスタ0
 */
#define		sarx0_addr		(*(volatile UINT8		*)0xFFFF7E)

#define		SARX0			sarx0_addr
 
/*
 *  第2スレーブアドレスレジスタ1
 */
#define		sarx1_addr		(*(volatile UINT8		*)0xFFFF86)

#define		SARX1			sarx1_addr

/*
 *  I2Cバスモードレジスタ0
 */
#define		icmr0_addr		(*(volatile UINT8		*)0xFFFF7F)

#define		ICMR0			icmr0_addr

/*
 *  I2Cバスモードレジスタ1
 */
#define		icmr1_addr		(*(volatile UINT8		*)0xFFFF87)

#define		ICMR1			icmr1_addr

/*
 *  I2Cバスコントロールレジスタ0
 */
#define		iccr0_addr		(*(volatile UINT8		*)0xFFFF78)

#define		ICCR0			iccr0_addr
 
/*
 *  I2Cバスコントロールレジスタ1
 */
#define		iccr1_addr		(*(volatile UINT8		*)0xFFFF80)

#define		ICCR1			iccr1_addr

/*
 *  I2Cバスステータスレジスタ0
 */
#define		icsr0_addr		(*(volatile UINT8		*)0xFFFF79)

#define		ICSR0			icsr0_addr

/*
 *  I2Cバスステータスレジスタ1
 */
#define		icsr1_addr		(*(volatile UINT8		*)0xFFFF81)

#define		ICSR1			icsr1_addr

/*
 *  シリアルコントロールレジスタX
 */
#define		scrx_addr		(*(volatile UINT8		*)0xFFFDB4)

#define		SCRX			scrx_addr

/*
 *  DDCスイッチレジスタ
 */
#define		ddcswr_addr		(*(volatile UINT8		*)0xFFFDB5)

#define		DDCSWR			ddcswr_addr


/********************************************************/
/*  コントローラエリアネットワーク						*/
/********************************************************/
/*
 *  マスタコントロールレジスタ
 */
/* ビットマスク値	*/
#define		RSTRQ_MSK		(UINT8)0x01u
#define		HLTRQ_MSK		(UINT8)0x02u
#define		MTM_MSK			(UINT8)0x04u
#define		SLPM_MSK		(UINT8)0x20u
#define		SLPMR_MSK		(UINT8)0x80u

/*
 *  マスタコントロールレジスタ 0
 */
#define		mcr0_addr		(*(volatile UINT8		*)0xFFF800)

#define		MCR0			mcr0_addr

/*
 *  マスタコントロールレジスタ 1
 */
#define		mcr1_addr		(*(volatile UINT8		*)0xFFFA00)

#define		MCR1			mcr1_addr

/*
 *  ジェネラルステータスレジスタ
 */
/* ビットマスク値	*/
#define		BOF_MSK			(UINT8)0x01u
#define		TRWF_MSK		(UINT8)0x02u
#define		MTSF_MSK		(UINT8)0x04u
#define		RSB_MSK			(UINT8)0x08u

/*
 *  ジェネラルステータスレジスタ 0
 */
#define		gsr0_addr		(*(volatile UINT8		*)0xFFF801)

#define		GSR0			gsr0_addr

/*
 *  ジェネラルステータスレジスタ 1
 */
#define		gsr1_addr		(*(volatile UINT8		*)0xFFFA01)

#define		GSR1			gsr1_addr

/*
 *  ビットコンフィグレジスタ
 */
typedef union {
	struct {
		UINT8	bitcr_low;	/* RW BCR下位8bit								*/
		UINT8	bitcr_high;	/* RW BCR上位8bit								*/
	} byte;
	UINT16	word;			/* RW BCR 32bit									*/
} BITCR_TYPE;

/* ビットマスク値	*/
#define		TSEG1_MSK8		(UINT8)0x0Fu
#define		TSEG2_MSK8		(UINT8)0x70u
#define		BSP_MSK8		(UINT8)0x80u
#define		BRP_MSK8		(UINT8)0x3Fu
#define		SJW_MSK8		(UINT8)0xC0u
#define		TSEG1_MSK16		(UINT16)0x000Fu
#define		TSEG2_MSK16		(UINT16)0x0070u
#define		BSP_MSK16		(UINT16)0x0080u
#define		BRP_MSK16		(UINT16)0x3F00u
#define		SJW_MSK16		(UINT16)0xC000u

/*
 *  ビットコンフィグレジスタ0
 */
#define		bitcr0_addr		(*(volatile BITCR_TYPE	*)0xFFF802)

#define		BITCR0			bitcr0_addr.word
#define		BITCR0L			bitcr0_addr.byte.bitcr_low
#define		BITCR0H			bitcr0_addr.byte.bitcr_high

/*
 *  ビットコンフィグレジスタ1
 */
#define		bitcr1_addr		(*(volatile BITCR_TYPE	*)0xFFFA02)

#define		BITCR1			bitcr1_addr.word
#define		BITCR1L			bitcr1_addr.byte.bitcr_low
#define		BITCR1H			bitcr1_addr.byte.bitcr_high

/*
 *  メールボックスコンフィグレジスタ
 */
typedef union {
	struct {
		UINT8	mbcr_low;
		UINT8	mbcr_high;
	} byte;
	UINT16 word;
} MBCR_TYPE;

/* ビットマスク値	*/
#define		MBCR1_MSK		(UINT16)0x0200u
#define		MBCR2_MSK		(UINT16)0x0400u
#define		MBCR3_MSK		(UINT16)0x0800u
#define		MBCR4_MSK		(UINT16)0x1000u
#define		MBCR5_MSK		(UINT16)0x2000u
#define		MBCR6_MSK		(UINT16)0x4000u
#define		MBCR7_MSK		(UINT16)0x8000u
#define		MBCR8_MSK		(UINT16)0x0001u
#define		MBCR9_MSK		(UINT16)0x0002u
#define		MBCR10_MSK		(UINT16)0x0004u
#define		MBCR11_MSK		(UINT16)0x0008u
#define		MBCR12_MSK		(UINT16)0x0010u
#define		MBCR13_MSK		(UINT16)0x0020u
#define		MBCR14_MSK		(UINT16)0x0040u
#define		MBCR15_MSK		(UINT16)0x0080u

/*
 *  メールボックスコンフィグレジスタ0
 */
#define		mbcr0_addr		(*(volatile MBCR_TYPE	*)0xFFF804)

#define		MBCR0			mbcr0_addr.word
#define		MBCR0H			mbcr0_addr.byte.mbcr_high
#define		MBCR0L			mbcr0_addr.byte.mbcr_low
 
/*
 *  メールボックスコンフィグレジスタ1
 */
#define		mbcr1_addr		(*(volatile MBCR_TYPE	*)0xFFFA04)
 
#define		MBCR1			mbcr1_addr.word
#define		MBCR1H			mbcr1_addr.byte.mbcr_high
#define		MBCR1L			mbcr1_addr.byte.mbcr_low

/*
 *  送信待ちレジスタ
 */
typedef union {
	struct {
		UINT8	txpr_low;
		UINT8	txpr_high;
	} byte;
	UINT16	word;
} TXPR_TYPE;

/* ビットマスク値	*/
#define		TXPR1_MSK		(UINT16)0x0200u
#define		TXPR2_MSK		(UINT16)0x0400u
#define		TXPR3_MSK		(UINT16)0x0800u
#define		TXPR4_MSK		(UINT16)0x1000u
#define		TXPR5_MSK		(UINT16)0x2000u
#define		TXPR6_MSK		(UINT16)0x4000u
#define		TXPR7_MSK		(UINT16)0x8000u
#define		TXPR8_MSK		(UINT16)0x0001u
#define		TXPR9_MSK		(UINT16)0x0002u
#define		TXPR10_MSK		(UINT16)0x0004u
#define		TXPR11_MSK		(UINT16)0x0008u
#define		TXPR12_MSK		(UINT16)0x0010u
#define		TXPR13_MSK		(UINT16)0x0020u
#define		TXPR14_MSK		(UINT16)0x0040u
#define		TXPR15_MSK		(UINT16)0x0080u

/*
 *  送信待ちレジスタ0
 */
#define		txpr0_addr		(*(volatile TXPR_TYPE	*)0xFFF806)

#define		TXPR0			txpr0_addr.word
#define		TXPR0H			txpr0_addr.byte.txpr_high
#define		TXPR0L			txpr0_addr.byte.txpr_low

/*
 *  送信待ちレジスタ1
 */
#define		txpr1_addr		(*(volatile TXPR_TYPE	*)0xFFFA06)

#define		TXPR1			txpr1_addr.word
#define		TXPR1H			txpr1_addr.byte.txpr_high
#define		TXPR1L			txpr1_addr.byte.txpr_low

/*
 *  送信待ち取り消しレジスタ
 */
typedef union {
	struct {
		UINT8	txcr_low;
		UINT8	txcr_high;
	} byte;
	UINT16	word;
} TXCR_TYPE;

/* ビットマスク値	*/
#define		TXCR1_MSK		(UINT16)0x0200u
#define		TXCR2_MSK		(UINT16)0x0400u
#define		TXCR3_MSK		(UINT16)0x0800u
#define		TXCR4_MSK		(UINT16)0x1000u
#define		TXCR5_MSK		(UINT16)0x2000u
#define		TXCR6_MSK		(UINT16)0x4000u
#define		TXCR7_MSK		(UINT16)0x8000u
#define		TXCR8_MSK		(UINT16)0x0001u
#define		TXCR9_MSK		(UINT16)0x0002u
#define		TXCR10_MSK		(UINT16)0x0004u
#define		TXCR11_MSK		(UINT16)0x0008u
#define		TXCR12_MSK		(UINT16)0x0010u
#define		TXCR13_MSK		(UINT16)0x0020u
#define		TXCR14_MSK		(UINT16)0x0040u
#define		TXCR15_MSK		(UINT16)0x0080u

/*
 *  送信待ち取り消しレジスタ0
 */
#define		txcr0_addr		(*(volatile TXCR_TYPE	*)0xFFF808)

#define		TXCR0			txcr0_addr.word
#define		TXCR0H			txcr0_addr.byte.txcr_high
#define		TXCR0L			txcr0_addr.byte.txcr_low
 
/*
 *  送信待ち取り消しレジスタ1
 */
#define		txcr1_addr		(*(volatile TXCR_TYPE	*)0xFFFA08)

#define		TXCR1			txcr1_addr.word
#define		TXCR1H			txcr1_addr.byte.txcr_high
#define		TXCR1L			txcr1_addr.byte.txcr_low

/*
 *  送信アクノレッジレジスタ
 */
typedef union {
	struct {
		UINT8	txack_low;
		UINT8	txack_high;
	} byte;
	UINT16 word;
} TXACK_TYPE;

/* ビットマスク値	*/
#define		TXACK1_MSK		(UINT16)0x0200u
#define		TXACK2_MSK		(UINT16)0x0400u
#define		TXACK3_MSK		(UINT16)0x0800u
#define		TXACK4_MSK		(UINT16)0x1000u
#define		TXACK5_MSK		(UINT16)0x2000u
#define		TXACK6_MSK		(UINT16)0x4000u
#define		TXACK7_MSK		(UINT16)0x8000u
#define		TXACK8_MSK		(UINT16)0x0001u
#define		TXACK9_MSK		(UINT16)0x0002u
#define		TXACK10_MSK		(UINT16)0x0004u
#define		TXACK11_MSK		(UINT16)0x0008u
#define		TXACK12_MSK		(UINT16)0x0010u
#define		TXACK13_MSK		(UINT16)0x0020u
#define		TXACK14_MSK		(UINT16)0x0040u
#define		TXACK15_MSK		(UINT16)0x0080u

/*
 *  送信アクノレッジレジスタ0
 */
#define		txack0_addr		(*(volatile TXACK_TYPE	*)0xFFF80A)

#define		TXACK0			txack0_addr.word
#define		TXACK0H			txack0_addr.byte.txack_high
#define		TXACK0L			txack0_addr.byte.txack_low
 
/*
 *  送信アクノレッジレジスタ1
 */
#define		txack1_addr		(*(volatile TXACK_TYPE	*)0xFFFA0A)

#define		TXACK1			txack1_addr.word
#define		TXACK1H			txack1_addr.byte.txack_high
#define		TXACK1L			txack1_addr.byte.txack_low

/*
 *  取り消しアクノレッジレジスタ
 */
typedef union {
	struct {
		UINT8	aback_low;
		UINT8	aback_high;
	} byte;
	UINT16	word;
} ABACK_TYPE;

/* ビットマスク値	*/
#define		ABACK1_MSK		(UINT16)0x0200u
#define		ABACK2_MSK		(UINT16)0x0400u
#define		ABACK3_MSK		(UINT16)0x0800u
#define		ABACK4_MSK		(UINT16)0x1000u
#define		ABACK5_MSK		(UINT16)0x2000u
#define		ABACK6_MSK		(UINT16)0x4000u
#define		ABACK7_MSK		(UINT16)0x8000u
#define		ABACK8_MSK		(UINT16)0x0001u
#define		ABACK9_MSK		(UINT16)0x0002u
#define		ABACK10_MSK		(UINT16)0x0004u
#define		ABACK11_MSK		(UINT16)0x0008u
#define		ABACK12_MSK		(UINT16)0x0010u
#define		ABACK13_MSK		(UINT16)0x0020u
#define		ABACK14_MSK		(UINT16)0x0040u
#define		ABACK15_MSK		(UINT16)0x0080u

/*
 *  取り消しアクノレッジレジスタ0
 */
#define		aback0_addr		(*(volatile ABACK_TYPE	*)0xFFF80C)

#define		ABACK0			aback0_addr.word
#define		ABACK0H			aback0_addr.byte.aback_high
#define		ABACK0L			aback0_addr.byte.aback_low

/*
 *  取り消しアクノレッジレジスタ1
 */
#define		aback1_addr		(*(volatile ABACK_TYPE	*)0xFFFA0C)

#define		ABACK1			aback1_addr.word
#define		ABACK1H			aback1_addr.byte.aback_high
#define		ABACK1L			aback1_addr.byte.aback_low

/*
 *  受信完了レジスタ
 */
typedef union {
	struct{
		UINT8	rxpr_low;
		UINT8	rxpr_high;
	} byte;
	UINT16	word;
} RXPR_TYPE;

/* ビットマスク値	*/
#define		RXPR0_MSK		(UINT16)0x0100u
#define		RXPR1_MSK		(UINT16)0x0200u
#define		RXPR2_MSK		(UINT16)0x0400u
#define		RXPR3_MSK		(UINT16)0x0800u
#define		RXPR4_MSK		(UINT16)0x1000u
#define		RXPR5_MSK		(UINT16)0x2000u
#define		RXPR6_MSK		(UINT16)0x4000u
#define		RXPR7_MSK		(UINT16)0x8000u
#define		RXPR8_MSK		(UINT16)0x0001u
#define		RXPR9_MSK		(UINT16)0x0002u
#define		RXPR10_MSK		(UINT16)0x0004u
#define		RXPR11_MSK		(UINT16)0x0008u
#define		RXPR12_MSK		(UINT16)0x0010u
#define		RXPR13_MSK		(UINT16)0x0020u
#define		RXPR14_MSK		(UINT16)0x0040u
#define		RXPR15_MSK		(UINT16)0x0080u

/*
 *  受信完了レジスタ0
 */
#define		rxpr0_addr		(*(volatile RXPR_TYPE	*)0xFFF80E)

#define		RXPR0			rxpr0_addr.word
#define		RXPR0H			rxpr0_addr.byte.rxpr_high
#define		RXPR0L			rxpr0_addr.byte.rxpr_low
 
/*
 *  受信完了レジスタ1
 */
#define		rxpr1_addr		(*(volatile RXPR_TYPE	*)0xFFFA0E)

#define		RXPR1			rxpr1_addr.word
#define		RXPR1H			rxpr1_addr.byte.rxpr_high
#define		RXPR1L			rxpr1_addr.byte.rxpr_low

/*
 *  リモートリクエストレジスタ
 */
typedef union {
	struct {
		UINT8	rfpr_low;
		UINT8	rfpr_high;
	} byte;
	UINT16	word;
} RFPR_TYPE;

/* ビットマスク値	*/
#define		RFPR0_MSK		(UINT16)0x0100u
#define		RFPR1_MSK		(UINT16)0x0200u
#define		RFPR2_MSK		(UINT16)0x0400u
#define		RFPR3_MSK		(UINT16)0x0800u
#define		RFPR4_MSK		(UINT16)0x1000u
#define		RFPR5_MSK		(UINT16)0x2000u
#define		RFPR6_MSK		(UINT16)0x4000u
#define		RFPR7_MSK		(UINT16)0x8000u
#define		RFPR8_MSK		(UINT16)0x0001u
#define		RFPR9_MSK		(UINT16)0x0002u
#define		RFPR10_MSK		(UINT16)0x0004u
#define		RFPR11_MSK		(UINT16)0x0008u
#define		RFPR12_MSK		(UINT16)0x0010u
#define		RFPR13_MSK		(UINT16)0x0020u
#define		RFPR14_MSK		(UINT16)0x0040u
#define		RFPR15_MSK		(UINT16)0x0080u

/*
 *  リモートリクエストレジスタ0
 */
#define		rfpr0_addr		(*(volatile RFPR_TYPE	*)0xFFF810)

#define		RFPR0			rfpr0_addr.word
#define		RFPR0H			rfpr0_addr.byte.rfpr_high
#define		RFPR0L			rfpr0_addr.byte.rfpr_low

/*
 *  リモートリクエストレジスタ1
 */ 
#define		rfpr1_addr		(*(volatile RFPR_TYPE	*)0xFFFA10)

#define		RFPR1			rfpr1_addr.word
#define		RFPR1H			rfpr1_addr.byte.rfpr_high
#define		RFPR1L			rfpr1_addr.byte.rfpr_low

/*
 *  インタラプトレジスタ
 */
typedef union {
	struct {
		UINT8	irr_low;
		UINT8	irr_high;
	} byte;
	UINT16	word;
} IRR_TYPE;

/*	ビットマスク値	*/
#define		OLFIF_MSK		(UINT16)0x8000u
#define		BOFIF_MSK		(UINT16)0x4000u
#define		EPIF_MSK		(UINT16)0x2000u
#define		ROWIF_MSK		(UINT16)0x1000u
#define		TOWIF_MSK		(UINT16)0x0800u
#define		RFRIF_MSK		(UINT16)0x0400u
#define		RMIF_MSK		(UINT16)0x0200u
#define		RSTIF_MSK		(UINT16)0x0100u
#define		BOIF_MSK		(UINT16)0x0010u
#define		URIF_MSK		(UINT16)0x0002u
#define		MBEIF_MSK		(UINT16)0x0001u

/*
 *  インタラプトレジスタ0
 */
#define		irr0_addr		(*(volatile IRR_TYPE	*)0xFFF812)

#define		IRR0			irr0_addr.word
#define		IRR0H			irr0_addr.byte.irr_high
#define		IRR0L			irr0_addr.byte.irr_low

/*
 *  インタラプトレジスタ1
 */
#define		irr1_addr		(*(volatile IRR_TYPE	*)0xFFFA12)
 
#define		IRR1			irr1_addr.word
#define		IRR1H			irr1_addr.byte.irr_high
#define		IRR1L			irr1_addr.byte.irr_low

/*
 *  メールボックスインタラプトマスクレジスタ
 */
typedef union {
	struct {
		UINT8	mbimr_low;
		UINT8	mbimr_high;
	} byte;
	UINT16	word;
} MBIMR_TYPE;

/* ビットマスク値	*/
#define		MBIMR0_MSK		(UINT16)0x0100u
#define		MBIMR1_MSK		(UINT16)0x0200u
#define		MBIMR2_MSK		(UINT16)0x0400u
#define		MBIMR3_MSK		(UINT16)0x0800u
#define		MBIMR4_MSK		(UINT16)0x1000u
#define		MBIMR5_MSK		(UINT16)0x2000u
#define		MBIMR6_MSK		(UINT16)0x4000u
#define		MBIMR7_MSK		(UINT16)0x8000u
#define		MBIMR8_MSK		(UINT16)0x0001u
#define		MBIMR9_MSK		(UINT16)0x0002u
#define		MBIMR10_MSK		(UINT16)0x0004u
#define		MBIMR11_MSK		(UINT16)0x0008u
#define		MBIMR12_MSK		(UINT16)0x0010u
#define		MBIMR13_MSK		(UINT16)0x0020u
#define		MBIMR14_MSK		(UINT16)0x0040u
#define		MBIMR15_MSK		(UINT16)0x0080u

/*
 *  メールボックスインタラプトマスクレジスタ0
 */
#define		mbimr0_addr		(*(volatile MBIMR_TYPE	*)0xFFF814)

#define		MBIMR0			mbimr0_addr.word
#define		MBIMR0H			mbimr0_addr.byte.mbimr_high
#define		MBIMR0L			mbimr0_addr.byte.mbimr_low

/*
 *  メールボックスインタラプトマスクレジスタ1
 */
#define		mbimr1_addr		(*(volatile MBIMR_TYPE	*)0xFFFA14)

#define		MBIMR1			mbimr1_addr.word
#define		MBIMR1H			mbimr1_addr.byte.mbimr_high
#define		MBIMR1L			mbimr1_addr.byte.mbimr_low

/*
 *  インタラプトマスクレジスタ
 */
typedef union {
	struct {
		UINT8	imr_low;
		UINT8	imr_high;
	} byte;
	UINT16	word;
} IMR_TYPE;

/* ビットマスク値	*/
#define		MBEIM_MSK		(UINT16)0x0001u
#define		URIM_MSK		(UINT16)0x0002u
#define		BOIM_MSK		(UINT16)0x0010u
#define		RMIM_MSK		(UINT16)0x0200u
#define		RFRIM_MSK		(UINT16)0x0400u
#define		TOWIM_MSK		(UINT16)0x0800u
#define		ROWIM_MSK		(UINT16)0x1000u
#define		EPIM_MSK		(UINT16)0x2000u
#define		BOFIM_MSK		(UINT16)0x4000u
#define		OLFIM_MSK		(UINT16)0x8000u

/*
 *  インタラプトマスクレジスタ0
 */
#define		imr0_addr		(*(volatile IMR_TYPE	*)0xFFF816)

#define		IMR0			imr0_addr.word
#define		IMR0H			imr0_addr.byte.imr_high
#define		IMR0L			imr0_addr.byte.imr_low

/*
 *  インタラプトマスクレジスタ1
 */
#define		imr1_addr		(*(volatile IMR_TYPE	*)0xFFFA16)

#define		IMR1			imr1_addr.word
#define		IMR1H			imr1_addr.byte.imr_high
#define		IMR1L			imr1_addr.byte.imr_low

/*
 *  受信エラーカウンタ0
 */
#define		rec0_addr		(*(volatile UINT8		*)0xFFF818)

#define		REC0			rec0_addr

/*
 *  受信エラーカウンタ1
 */
#define		rec1_addr		(*(volatile UINT8		*)0xFFFA18)

#define		REC1			rec1_addr

/*
 *  送信エラーカウンタ0
 */
#define		tec0_addr		(*(volatile UINT8		*)0xFFF819)

#define		TEC0			tec0_addr

/*
 *  送信エラーカウンタ1
 */
#define		tec1_addr		(*(volatile UINT8		*)0xFFFA19)

#define		TEC1			tec1_addr

/*
 *  未読メッセージステータスレジスタ
 */
typedef union {
	struct {
		UINT8	umsr_low;
		UINT8	umsr_high;
	} byte;
	UINT16		word;
} UMSR_TYPE;

/* ビットマスク値	*/
#define		UMSR0_MSK		(UINT16)0x0100u
#define		UMSR1_MSK		(UINT16)0x0200u
#define		UMSR2_MSK		(UINT16)0x0400u
#define		UMSR3_MSK		(UINT16)0x0800u
#define		UMSR4_MSK		(UINT16)0x1000u
#define		UMSR5_MSK		(UINT16)0x2000u
#define		UMSR6_MSK		(UINT16)0x4000u
#define		UMSR7_MSK		(UINT16)0x8000u
#define		UMSR8_MSK		(UINT16)0x0001u
#define		UMSR9_MSK		(UINT16)0x0002u
#define		UMSR10_MSK		(UINT16)0x0004u
#define		UMSR11_MSK		(UINT16)0x0008u
#define		UMSR12_MSK		(UINT16)0x0010u
#define		UMSR13_MSK		(UINT16)0x0020u
#define		UMSR14_MSK		(UINT16)0x0040u
#define		UMSR15_MSK		(UINT16)0x0080u

/*
 *  未読メッセージステータスレジスタ0
 */
#define		umsr0_addr		(*(volatile UMSR_TYPE	*)0xFFF81A)

#define		UMSR0			umsr0_addr.word
#define		UMSR0H			umsr0_addr.byte.umsr_high
#define		UMSR0L			umsr0_addr.byte.umsr_low

/*
 *  未読メッセージステータスレジスタ1
 */
#define		umsr1_addr		(*(volatile UMSR_TYPE	*)0xFFFA1A)

#define		UMSR1			umsr1_addr.word
#define		UMSR1H			umsr1_addr.byte.umsr_high
#define		UMSR1L			umsr1_addr.byte.umsr_low

/*
 *  ローカルアクセプタンスフィルタマスク
 */
typedef union {
	struct {
		UINT8	lafm_low;
		UINT8	lafm_high;
	} byte;
	UINT16	word;
} LAFM_TYPE;

/* ビットマスク値	*/
#define		LAFM0_MSK		(UINT16)0x0100u
#define		LAFM1_MSK		(UINT16)0x0200u
#define		LAFM2_MSK		(UINT16)0x0400u
#define		LAFM3_MSK		(UINT16)0x0800u
#define		LAFM4_MSK		(UINT16)0x1000u
#define		LAFM5_MSK		(UINT16)0x2000u
#define		LAFM6_MSK		(UINT16)0x4000u
#define		LAFM7_MSK		(UINT16)0x8000u
#define		LAFM8_MSK		(UINT16)0x0001u
#define		LAFM9_MSK		(UINT16)0x0002u
#define		LAFM10_MSK		(UINT16)0x0004u
#define		LAFM11_MSK		(UINT16)0x0008u
#define		LAFM12_MSK		(UINT16)0x0010u
#define		LAFM13_MSK		(UINT16)0x0020u
#define		LAFM14_MSK		(UINT16)0x0040u
#define		LAFM15_MSK		(UINT16)0x0080u

/*
 *  ローカルアクセプタンスフィルタマスク0L
 */
#define		lafm0l_addr		(*(volatile LAFM_TYPE	*)0xFFF81C)

#define		LAFM0L			lafm0l_addr.word
#define		LAFM0LH			lafm0l_addr.byte.lafm_high
#define		LAFM0LL			lafm0l_addr.byte.lafm_low

/*
 *  ローカルアクセプタンスフィルタマスク1L
 */
#define		lafm1l_addr		(*(volatile LAFM_TYPE	*)0xFFFA1C)

#define		LAFM1L			lafm1l_addr.word
#define		LAFM1LH			lafm1l_addr.byte.lafm_high
#define		LAFM1LL			lafm1l_addr.byte.lafm_low

/*
 *  ローカルアクセプタンスフィルタマスク0H
 */
#define		lafm0h_addr		(*(volatile LAFM_TYPE	*)0xFFF81E)

#define		LAFM0H			lafm0h_addr.word
#define		LAFM0HH			lafm0h_addr.byte.lafm_high
#define		LAFM0HL			lafm0h_addr.byte.lafm_low

/*
 *  ローカルアクセプタンスフィルタマスク1H
 */
#define		lafm1h_addr		(*(volatile LAFM_TYPE	*)0xFFFA1E)

#define		LAFM1H			lafm1h_addr.word
#define		LAFM1HH			lafm1h_addr.byte.lafm_high
#define		LAFM1HL			lafm1h_addr.byte.lafm_low

/*
 *  メッセージコントロール
 */
typedef struct {
	UINT8	dlc;
	UINT8	no_assign2;
	UINT8	no_assign3;
	UINT8	no_assign4;
	UINT8	sid0;
	UINT8	sid1;
	UINT8	eid0;
	UINT8	eid1;
} MC_TYPE;

/* ビットマスク値			*/
#define		DLC_MSK			(UINT8)0x0Fu
#define		IDE_MSK			(UINT8)0x08u
#define		RTR_MSK			(UINT8)0x10u

/*
 *  メッセージコントロール00
 */
#define		mc00_addr		(*(volatile MC_TYPE		*)0xFFF820)

#define		DLC_MC00		mc00_addr.dlc
#define		SID0_MC00		mc00_addr.sid0
#define		SID1_MC00		mc00_addr.sid1
#define		EID0_MC00		mc00_addr.eid0
#define		EID1_MC00		mc00_addr.eid1

/*
 *  メッセージコントロール01
 */
#define		mc01_addr		(*(volatile MC_TYPE		*)0xFFF828)

#define		DLC_MC01		mc01_addr.dlc
#define		SID0_MC01		mc01_addr.sid0
#define		SID1_MC01		mc01_addr.sid1
#define		EID0_MC01		mc01_addr.eid0
#define		EID1_MC01		mc01_addr.eid1

/*
 *  メッセージコントロール02
 */
#define		mc02_addr		(*(volatile MC_TYPE		*)0xFFF830)

#define		DLC_MC02		mc02_addr.dlc
#define		SID0_MC02		mc02_addr.sid0
#define		SID1_MC02		mc02_addr.sid1
#define		EID0_MC02		mc02_addr.eid0
#define		EID1_MC02		mc02_addr.eid1

/*
 *  メッセージコントロール03
 */
#define		mc03_addr		(*(volatile MC_TYPE		*)0xFFF838)

#define		DLC_MC03		mc03_addr.dlc
#define		SID0_MC03		mc03_addr.sid0
#define		SID1_MC03		mc03_addr.sid1
#define		EID0_MC03		mc03_addr.eid0
#define		EID1_MC03		mc03_addr.eid1

/*
 *  メッセージコントロール04
 */
#define		mc04_addr		(*(volatile MC_TYPE		*)0xFFF840)

#define		DLC_MC04		mc04_addr.dlc
#define		SID0_MC04		mc04_addr.sid0
#define		SID1_MC04		mc04_addr.sid1
#define		EID0_MC04		mc04_addr.eid0
#define		EID1_MC04		mc04_addr.eid1

/*
 *  メッセージコントロール05
 */
#define		mc05_addr		(*(volatile MC_TYPE		*)0xFFF848)

#define		DLC_MC05		mc05_addr.dlc
#define		SID0_MC05		mc05_addr.sid0
#define		SID1_MC05		mc05_addr.sid1
#define		EID0_MC05		mc05_addr.eid0
#define		EID1_MC05		mc05_addr.eid1

/*
 *  メッセージコントロール06
 */
#define		mc06_addr		(*(volatile MC_TYPE		*)0xFFF850)

#define		DLC_MC06		mc06_addr.dlc
#define		SID0_MC06		mc06_addr.sid0
#define		SID1_MC06		mc06_addr.sid1
#define		EID0_MC06		mc06_addr.eid0
#define		EID1_MC06		mc06_addr.eid1

/*
 *  メッセージコントロール07
 */
#define		mc07_addr		(*(volatile MC_TYPE		*)0xFFF858)

#define		DLC_MC07		mc07_addr.dlc
#define		SID0_MC07		mc07_addr.sid0
#define		SID1_MC07		mc07_addr.sid1
#define		EID0_MC07		mc07_addr.eid0
#define		EID1_MC07		mc07_addr.eid1

/*
 *  メッセージコントロール08
 */
#define		mc08_addr		(*(volatile MC_TYPE		*)0xFFF860)

#define		DLC_MC08		mc08_addr.dlc
#define		SID0_MC08		mc08_addr.sid0
#define		SID1_MC08		mc08_addr.sid1
#define		EID0_MC08		mc08_addr.eid0
#define		EID1_MC08		mc08_addr.eid1

/*
 *  メッセージコントロール09
 */
#define		mc09_addr		(*(volatile MC_TYPE		*)0xFFF868)

#define		DLC_MC09		mc09_addr.dlc
#define		SID0_MC09		mc09_addr.sid0
#define		SID1_MC09		mc09_addr.sid1
#define		EID0_MC09		mc09_addr.eid0
#define		EID1_MC09		mc09_addr.eid1

/*
 *  メッセージコントロール010
 */
#define		mc010_addr		(*(volatile MC_TYPE		*)0xFFF870)

#define		DLC_MC010		mc010_addr.dlc
#define		SID0_MC010		mc010_addr.sid0
#define		SID1_MC010		mc010_addr.sid1
#define		EID0_MC010		mc010_addr.eid0
#define		EID1_MC010		mc010_addr.eid1

/*
 *  メッセージコントロール011
 */
#define		mc011_addr		(*(volatile MC_TYPE		*)0xFFF878)

#define		DLC_MC011		mc011_addr.dlc
#define		SID0_MC011		mc011_addr.sid0
#define		SID1_MC011		mc011_addr.sid1
#define		EID0_MC011		mc011_addr.eid0
#define		EID1_MC011		mc011_addr.eid1

/*
 *  メッセージコントロール012
 */
#define		mc012_addr		(*(volatile MC_TYPE		*)0xFFF880)

#define		DLC_MC012		mc012_addr.dlc
#define		SID0_MC012		mc012_addr.sid0
#define		SID1_MC012		mc012_addr.sid1
#define		EID0_MC012		mc012_addr.eid0
#define		EID1_MC012		mc012_addr.eid1

/*
 *  メッセージコントロール013
 */
#define		mc013_addr		(*(volatile MC_TYPE		*)0xFFF888)

#define		DLC_MC013		mc013_addr.dlc
#define		SID0_MC013		mc013_addr.sid0
#define		SID1_MC013		mc013_addr.sid1
#define		EID0_MC013		mc013_addr.eid0
#define		EID1_MC013		mc013_addr.eid1

/*
 *  メッセージコントロール014
 */
#define		mc014_addr		(*(volatile MC_TYPE		*)0xFFF890)

#define		DLC_MC014		mc014_addr.dlc
#define		SID0_MC014		mc014_addr.sid0
#define		SID1_MC014		mc014_addr.sid1
#define		EID0_MC014		mc014_addr.eid0
#define		EID1_MC014		mc014_addr.eid1

/*
 *  メッセージコントロール015
 */
#define		mc015_addr		(*(volatile MC_TYPE		*)0xFFF898)

#define		DLC_MC015		mc015_addr.dlc
#define		SID0_MC015		mc015_addr.sid0
#define		SID1_MC015		mc015_addr.sid1
#define		EID0_MC015		mc015_addr.eid0
#define		EID1_MC015		mc015_addr.eid1

/*
 *  メッセージコントロール10
 */
#define		mc10_addr		(*(volatile MC_TYPE		*)0xFFFA20)

#define		DLC_MC10		mc10_addr.dlc
#define		SID0_MC10		mc10_addr.sid0
#define		SID1_MC10		mc10_addr.sid1
#define		EID0_MC10		mc10_addr.eid0
#define		EID1_MC10		mc10_addr.eid1

/*
 *  メッセージコントロール11
 */
#define		mc11_addr		(*(volatile MC_TYPE		*)0xFFFA28)

#define		DLC_MC11		mc11_addr.dlc
#define		SID0_MC11		mc11_addr.sid0
#define		SID1_MC11		mc11_addr.sid1
#define		EID0_MC11		mc11_addr.eid0
#define		EID1_MC11		mc11_addr.eid1

/*
 *  メッセージコントロール12
 */
#define		mc12_addr		(*(volatile MC_TYPE		*)0xFFFA30)

#define		DLC_MC12		mc12_addr.dlc
#define		SID0_MC12		mc12_addr.sid0
#define		SID1_MC12		mc12_addr.sid1
#define		EID0_MC12		mc12_addr.eid0
#define		EID1_MC12		mc12_addr.eid1

/*
 *  メッセージコントロール13
 */
#define		mc13_addr		(*(volatile MC_TYPE		*)0xFFFA38)

#define		DLC_MC13		mc13_addr.dlc
#define		SID0_MC13		mc13_addr.sid0
#define		SID1_MC13		mc13_addr.sid1
#define		EID0_MC13		mc13_addr.eid0
#define		EID1_MC13		mc13_addr.eid1

/*
 *  メッセージコントロール14
 */
#define		mc14_addr		(*(volatile MC_TYPE		*)0xFFFA40)

#define		DLC_MC14		mc14_addr.dlc
#define		SID0_MC14		mc14_addr.sid0
#define		SID1_MC14		mc14_addr.sid1
#define		EID0_MC14		mc14_addr.eid0
#define		EID1_MC14		mc14_addr.eid1

/*
 *  メッセージコントロール15
 */
#define		mc15_addr		(*(volatile MC_TYPE		*)0xFFFA48)

#define		DLC_MC15		mc15_addr.dlc
#define		SID0_MC15		mc15_addr.sid0
#define		SID1_MC15		mc15_addr.sid1
#define		EID0_MC15		mc15_addr.eid0
#define		EID1_MC15		mc15_addr.eid1

/*
 *  メッセージコントロール16
 */
#define		mc16_addr		(*(volatile MC_TYPE		*)0xFFFA50)

#define		DLC_MC16		mc16_addr.dlc
#define		SID0_MC16		mc16_addr.sid0
#define		SID1_MC16		mc16_addr.sid1
#define		EID0_MC16		mc16_addr.eid0
#define		EID1_MC16		mc16_addr.eid1

/*
 *  メッセージコントロール17
 */
#define		mc17_addr		(*(volatile MC_TYPE		*)0xFFFA58)

#define		DLC_MC17		mc17_addr.dlc
#define		SID0_MC17		mc17_addr.sid0
#define		SID1_MC17		mc17_addr.sid1
#define		EID0_MC17		mc17_addr.eid0
#define		EID1_MC17		mc17_addr.eid1

/*
 *  メッセージコントロール18
 */
#define		mc18_addr		(*(volatile MC_TYPE		*)0xFFFA60)

#define		DLC_MC18		mc18_addr.dlc
#define		SID0_MC18		mc18_addr.sid0
#define		SID1_MC18		mc18_addr.sid1
#define		EID0_MC18		mc18_addr.eid0
#define		EID1_MC18		mc18_addr.eid1

/*
 *  メッセージコントロール19
 */
#define		mc19_addr		(*(volatile MC_TYPE		*)0xFFFA68)

#define		DLC_MC19		mc19_addr.dlc
#define		SID0_MC19		mc19_addr.sid0
#define		SID1_MC19		mc19_addr.sid1
#define		EID0_MC19		mc19_addr.eid0
#define		EID1_MC19		mc19_addr.eid1

/*
 *  メッセージコントロール110
 */
#define		mc110_addr		(*(volatile MC_TYPE		*)0xFFFA70)

#define		DLC_MC110		mc110_addr.dlc
#define		SID0_MC110		mc110_addr.sid0
#define		SID1_MC110		mc110_addr.sid1
#define		EID0_MC110		mc110_addr.eid0
#define		EID1_MC110		mc110_addr.eid1

/*
 *  メッセージコントロール111
 */
#define		mc111_addr		(*(volatile MC_TYPE		*)0xFFFA78)

#define		DLC_MC111		mc111_addr.dlc
#define		SID0_MC111		mc111_addr.sid0
#define		SID1_MC111		mc111_addr.sid1
#define		EID0_MC111		mc111_addr.eid0
#define		EID1_MC111		mc111_addr.eid1

/*
 *  メッセージコントロール112
 */
#define		mc112_addr		(*(volatile MC_TYPE		*)0xFFFA80)

#define		DLC_MC112		mc112_addr.dlc
#define		SID0_MC112		mc112_addr.sid0
#define		SID1_MC112		mc112_addr.sid1
#define		EID0_MC112		mc112_addr.eid0
#define		EID1_MC112		mc112_addr.eid1

/*
 *  メッセージコントロール113
 */
#define		mc113_addr		(*(volatile MC_TYPE		*)0xFFFA88)

#define		DLC_MC113		mc113_addr.dlc
#define		SID0_MC113		mc113_addr.sid0
#define		SID1_MC113		mc113_addr.sid1
#define		EID0_MC113		mc113_addr.eid0
#define		EID1_MC113		mc113_addr.eid1

/*
 *  メッセージコントロール114
 */
#define		mc114_addr		(*(volatile MC_TYPE		*)0xFFFA90)

#define		DLC_MC114		mc114_addr.dlc
#define		SID0_MC114		mc114_addr.sid0
#define		SID1_MC114		mc114_addr.sid1
#define		EID0_MC114		mc114_addr.eid0
#define		EID1_MC114		mc114_addr.eid1

/*
 *  メッセージコントロール115
 */
#define		mc115_addr		(*(volatile MC_TYPE		*)0xFFFA98)

#define		DLC_MC115		mc115_addr.dlc
#define		SID0_MC115		mc115_addr.sid0
#define		SID1_MC115		mc115_addr.sid1
#define		EID0_MC115		mc115_addr.eid0
#define		EID1_MC115		mc115_addr.eid1

/*
 *  メッセージデータ00
 */
#define		md00_addr		((volatile UINT8		*)0xFFF8B0)

#define		MD000			md00_addr[0]
#define		MD001			md00_addr[1]
#define		MD002			md00_addr[2]
#define		MD003			md00_addr[3]
#define		MD004			md00_addr[4]
#define		MD005			md00_addr[5]
#define		MD006			md00_addr[6]
#define		MD007			md00_addr[7]

/*
 *  メッセージデータ01
 */
#define		md01_addr		((volatile UINT8		*)0xFFF8B8)

#define		MD010			md01_addr[0]
#define		MD011			md01_addr[1]
#define		MD012			md01_addr[2]
#define		MD013			md01_addr[3]
#define		MD014			md01_addr[4]
#define		MD015			md01_addr[5]
#define		MD016			md01_addr[6]
#define		MD017			md01_addr[7]

/*
 *  メッセージデータ02
 */
#define		md02_addr		((volatile UINT8		*)0xFFF8C0)

#define		MD020			md02_addr[0]
#define		MD021			md02_addr[1]
#define		MD022			md02_addr[2]
#define		MD023			md02_addr[3]
#define		MD024			md02_addr[4]
#define		MD025			md02_addr[5]
#define		MD026			md02_addr[6]
#define		MD027			md02_addr[7]

/*
 *  メッセージデータ03
 */
#define		md03_addr		((volatile UINT8		*)0xFFF8C8)

#define		MD030			md03_addr[0]
#define		MD031			md03_addr[1]
#define		MD032			md03_addr[2]
#define		MD033			md03_addr[3]
#define		MD034			md03_addr[4]
#define		MD035			md03_addr[5]
#define		MD036			md03_addr[6]
#define		MD037			md03_addr[7]

/*
 *  メッセージデータ04
 */
#define		md04_addr		((volatile UINT8		*)0xFFF8D0)

#define		MD040			md04_addr[0]
#define		MD041			md04_addr[1]
#define		MD042			md04_addr[2]
#define		MD043			md04_addr[3]
#define		MD044			md04_addr[4]
#define		MD045			md04_addr[5]
#define		MD046			md04_addr[6]
#define		MD047			md04_addr[7]

/*
 *  メッセージデータ05
 */
#define		md05_addr		((volatile UINT8		*)0xFFF8D8)

#define		MD050			md05_addr[0]
#define		MD051			md05_addr[1]
#define		MD052			md05_addr[2]
#define		MD053			md05_addr[3]
#define		MD054			md05_addr[4]
#define		MD055			md05_addr[5]
#define		MD056			md05_addr[6]
#define		MD057			md05_addr[7]

/*
 *  メッセージデータ06
 */
#define		md06_addr		((volatile UINT8		*)0xFFF8E0)

#define		MD060			md06_addr[0]
#define		MD061			md06_addr[1]
#define		MD062			md06_addr[2]
#define		MD063			md06_addr[3]
#define		MD064			md06_addr[4]
#define		MD065			md06_addr[5]
#define		MD066			md06_addr[6]
#define		MD067			md06_addr[7]

/*
 *  メッセージデータ07
 */
#define		md07_addr		((volatile UINT8		*)0xFFF8E8)

#define		MD070			md07_addr[0]
#define		MD071			md07_addr[1]
#define		MD072			md07_addr[2]
#define		MD073			md07_addr[3]
#define		MD074			md07_addr[4]
#define		MD075			md07_addr[5]
#define		MD076			md07_addr[6]
#define		MD077			md07_addr[7]

/*
 *  メッセージデータ08
 */
#define		md08_addr		((volatile UINT8		*)0xFFF8F0)

#define		MD080			md08_addr[0]
#define		MD081			md08_addr[1]
#define		MD082			md08_addr[2]
#define		MD083			md08_addr[3]
#define		MD084			md08_addr[4]
#define		MD085			md08_addr[5]
#define		MD086			md08_addr[6]
#define		MD087			md08_addr[7]

/*
 *  メッセージデータ09
 */
#define		md09_addr		((volatile UINT8		*)0xFFF8F8)

#define		MD090			md09_addr[0]
#define		MD091			md09_addr[1]
#define		MD092			md09_addr[2]
#define		MD093			md09_addr[3]
#define		MD094			md09_addr[4]
#define		MD095			md09_addr[5]
#define		MD096			md09_addr[6]
#define		MD097			md09_addr[7]

/*
 *  メッセージデータ010
 */
#define		md010_addr		((volatile UINT8		*)0xFFF900)

#define		MD0100			md010_addr[0]
#define		MD0101			md010_addr[1]
#define		MD0102			md010_addr[2]
#define		MD0103			md010_addr[3]
#define		MD0104			md010_addr[4]
#define		MD0105			md010_addr[5]
#define		MD0106			md010_addr[6]
#define		MD0107			md010_addr[7]

/*
 *  メッセージデータ011
 */
#define		md011_addr		((volatile UINT8		*)0xFFF908)

#define		MD0110			md011_addr[0]
#define		MD0111			md011_addr[1]
#define		MD0112			md011_addr[2]
#define		MD0113			md011_addr[3]
#define		MD0114			md011_addr[4]
#define		MD0115			md011_addr[5]
#define		MD0116			md011_addr[6]
#define		MD0117			md011_addr[7]

/*
 *  メッセージデータ012
 */
#define		md012_addr		((volatile UINT8		*)0xFFF910)

#define		MD0120			md012_addr[0]
#define		MD0121			md012_addr[1]
#define		MD0122			md012_addr[2]
#define		MD0123			md012_addr[3]
#define		MD0124			md012_addr[4]
#define		MD0125			md012_addr[5]
#define		MD0126			md012_addr[6]
#define		MD0127			md012_addr[7]

/*
 *  メッセージデータ013
 */
#define		md013_addr		((volatile UINT8		*)0xFFF918)

#define		MD0130			md013_addr[0]
#define		MD0131			md013_addr[1]
#define		MD0132			md013_addr[2]
#define		MD0133			md013_addr[3]
#define		MD0134			md013_addr[4]
#define		MD0135			md013_addr[5]
#define		MD0136			md013_addr[6]
#define		MD0137			md013_addr[7]

/*
 *  メッセージデータ014
 */
#define		md014_addr		((volatile UINT8		*)0xFFF920)

#define		MD0140			md014_addr[0]
#define		MD0141			md014_addr[1]
#define		MD0142			md014_addr[2]
#define		MD0143			md014_addr[3]
#define		MD0144			md014_addr[4]
#define		MD0145			md014_addr[5]
#define		MD0146			md014_addr[6]
#define		MD0147			md014_addr[7]

/*
 *  メッセージデータ015
 */
#define		md015_addr		((volatile UINT8		*)0xFFF928)

#define		MD0150			md015_addr[0]
#define		MD0151			md015_addr[1]
#define		MD0152			md015_addr[2]
#define		MD0153			md015_addr[3]
#define		MD0154			md015_addr[4]
#define		MD0155			md015_addr[5]
#define		MD0156			md015_addr[6]
#define		MD0157			md015_addr[7]

/*
 *  メッセージデータ10
 */
#define		md10_addr		((volatile UINT8		*)0xFFFAB0)

#define		MD100			md10_addr[0]
#define		MD101			md10_addr[1]
#define		MD102			md10_addr[2]
#define		MD103			md10_addr[3]
#define		MD104			md10_addr[4]
#define		MD105			md10_addr[5]
#define		MD106			md10_addr[6]
#define		MD107			md10_addr[7]

/*
 *  メッセージデータ11
 */
#define		md11_addr		((volatile UINT8		*)0xFFFAB8)

#define		MD110			md11_addr[0]
#define		MD111			md11_addr[1]
#define		MD112			md11_addr[2]
#define		MD113			md11_addr[3]
#define		MD114			md11_addr[4]
#define		MD115			md11_addr[5]
#define		MD116			md11_addr[6]
#define		MD117			md11_addr[7]

/*
 *  メッセージデータ12
 */
#define		md12_addr		((volatile UINT8		*)0xFFFAC0)

#define		MD120			md12_addr[0]
#define		MD121			md12_addr[1]
#define		MD122			md12_addr[2]
#define		MD123			md12_addr[3]
#define		MD124			md12_addr[4]
#define		MD125			md12_addr[5]
#define		MD126			md12_addr[6]
#define		MD127			md12_addr[7]

/*
 *  メッセージデータ13
 */
#define		md13_addr		((volatile UINT8		*)0xFFFAC8)

#define		MD130			md13_addr[0]
#define		MD131			md13_addr[1]
#define		MD132			md13_addr[2]
#define		MD133			md13_addr[3]
#define		MD134			md13_addr[4]
#define		MD135			md13_addr[5]
#define		MD136			md13_addr[6]
#define		MD137			md13_addr[7]

/*
 *  メッセージデータ14
 */
#define		md14_addr		((volatile UINT8		*)0xFFFAD0)

#define		MD140			md14_addr[0]
#define		MD141			md14_addr[1]
#define		MD142			md14_addr[2]
#define		MD143			md14_addr[3]
#define		MD144			md14_addr[4]
#define		MD145			md14_addr[5]
#define		MD146			md14_addr[6]
#define		MD147			md14_addr[7]

/*
 *  メッセージデータ15
 */
#define		md15_addr		((volatile UINT8		*)0xFFFAD8)

#define		MD150			md15_addr[0]
#define		MD151			md15_addr[1]
#define		MD152			md15_addr[2]
#define		MD153			md15_addr[3]
#define		MD154			md15_addr[4]
#define		MD155			md15_addr[5]
#define		MD156			md15_addr[6]
#define		MD157			md15_addr[7]

/*
 *  メッセージデータ16
 */
#define		md16_addr		((volatile UINT8		*)0xFFFAE0)

#define		MD160			md16_addr[0]
#define		MD161			md16_addr[1]
#define		MD162			md16_addr[2]
#define		MD163			md16_addr[3]
#define		MD164			md16_addr[4]
#define		MD165			md16_addr[5]
#define		MD166			md16_addr[6]
#define		MD167			md16_addr[7]

/*
 *  メッセージデータ17
 */
#define		md17_addr		((volatile UINT8		*)0xFFFAE8)

#define		MD170			md17_addr[0]
#define		MD171			md17_addr[1]
#define		MD172			md17_addr[2]
#define		MD173			md17_addr[3]
#define		MD174			md17_addr[4]
#define		MD175			md17_addr[5]
#define		MD176			md17_addr[6]
#define		MD177			md17_addr[7]

/*
 *  メッセージデータ18
 */
#define		md18_addr		((volatile UINT8		*)0xFFFAF0)

#define		MD180			md18_addr[0]
#define		MD181			md18_addr[1]
#define		MD182			md18_addr[2]
#define		MD183			md18_addr[3]
#define		MD184			md18_addr[4]
#define		MD185			md18_addr[5]
#define		MD186			md18_addr[6]
#define		MD187			md18_addr[7]

/*
 *  メッセージデータ19
 */
#define		md19_addr		((volatile UINT8		*)0xFFFAF8)

#define		MD190			md19_addr[0]
#define		MD191			md19_addr[1]
#define		MD192			md19_addr[2]
#define		MD193			md19_addr[3]
#define		MD194			md19_addr[4]
#define		MD195			md19_addr[5]
#define		MD196			md19_addr[6]
#define		MD197			md19_addr[7]

/*
 *  メッセージデータ110
 */
#define		md110_addr		((volatile UINT8		*)0xFFFB00)

#define		MD1100			md110_addr[0]
#define		MD1101			md110_addr[1]
#define		MD1102			md110_addr[2]
#define		MD1103			md110_addr[3]
#define		MD1104			md110_addr[4]
#define		MD1105			md110_addr[5]
#define		MD1106			md110_addr[6]
#define		MD1107			md110_addr[7]

/*
 *  メッセージデータ111
 */
#define		md111_addr		((volatile UINT8		*)0xFFFB08)

#define		MD1110			md111_addr[0]
#define		MD1111			md111_addr[1]
#define		MD1112			md111_addr[2]
#define		MD1113			md111_addr[3]
#define		MD1114			md111_addr[4]
#define		MD1115			md111_addr[5]
#define		MD1116			md111_addr[6]
#define		MD1117			md111_addr[7]

/*
 *  メッセージデータ112
 */
#define		md112_addr		((volatile UINT8		*)0xFFFB10)

#define		MD1120			md112_addr[0]
#define		MD1121			md112_addr[1]
#define		MD1122			md112_addr[2]
#define		MD1123			md112_addr[3]
#define		MD1124			md112_addr[4]
#define		MD1125			md112_addr[5]
#define		MD1126			md112_addr[6]
#define		MD1127			md112_addr[7]

/*
 *  メッセージデータ113
 */
#define		md113_addr		((volatile UINT8		*)0xFFFB18)

#define		MD1130			md113_addr[0]
#define		MD1131			md113_addr[1]
#define		MD1132			md113_addr[2]
#define		MD1133			md113_addr[3]
#define		MD1134			md113_addr[4]
#define		MD1135			md113_addr[5]
#define		MD1136			md113_addr[6]
#define		MD1137			md113_addr[7]

/*
 *  メッセージデータ114
 */
#define		md114_addr		((volatile UINT8		*)0xFFFB20)

#define		MD1140			md114_addr[0]
#define		MD1141			md114_addr[1]
#define		MD1142			md114_addr[2]
#define		MD1143			md114_addr[3]
#define		MD1144			md114_addr[4]
#define		MD1145			md114_addr[5]
#define		MD1146			md114_addr[6]
#define		MD1147			md114_addr[7]

/*
 *  メッセージデータ115
 */
#define		md115_addr		((volatile UINT8		*)0xFFFB28)

#define		MD1150			md115_addr[0]
#define		MD1151			md115_addr[1]
#define		MD1152			md115_addr[2]
#define		MD1153			md115_addr[3]
#define		MD1154			md115_addr[4]
#define		MD1155			md115_addr[5]
#define		MD1156			md115_addr[6]
#define		MD1157			md115_addr[7]


/********************************************************/
/*  A/D変換機											*/
/********************************************************/
/*
 *  A/Dデータレジスタ
 */
typedef union {
	struct {
		UINT8	ad_high;
		UINT8	ad_low;
	} byte;
	UINT16		word;
} ADDR_TYPE;

/*
 *  A/DデータレジスタA
 */
#define		addra_addr		(*(volatile ADDR_TYPE	*)0xFFFF90)

#define		ADDRA			addra_addr.word
#define		ADDRAH			addra_addr.byte.ad_high
#define		ADDRAL			addra_addr.byte.ad_low

/*
 *  A/DデータレジスタB
 */
#define		addrb_addr		(*(volatile ADDR_TYPE	*)0xFFFF92)

#define		ADDRB			addrb_addr.word
#define		ADDRBH			addrb_addr.byte.ad_high
#define		ADDRBL			addrb_addr.byte.ad_low

/*
 *  A/DデータレジスタC
 */
#define		addrc_addr		(*(volatile ADDR_TYPE	*)0xFFFF94)

#define		ADDRC			addrc_addr.word
#define		ADDRCH			addrc_addr.byte.ad_high
#define		ADDRCL			addrc_addr.byte.ad_low

/*
 *  A/DデータレジスタD
 */
#define		addrd_addr		(*(volatile ADDR_TYPE	*)0xFFFF96)

#define		ADDRD			addrd_addr.word
#define		ADDRDH			addrd_addr.byte.ad_high
#define		ADDRDL			addrd_addr.byte.ad_low

/*
 *  A/Dコントロール/ステータスレジスタ
 */
#define		adcsr_addr		(*(volatile UINT8		*)0xFFFF98)

#define		ADCSR			adcsr_addr

/*
 *  A/Dコントロールレジスタ
 */
#define		adcr_addr		(*(volatile UINT8		*)0xFFFF99)

#define		ADCR			adcr_addr


/*********************************************************/
/*  D/A変換機											**/
/*********************************************************/
/*
 *  D/Aデータレジスタ0
 */
#define		dadr0_addr		(*(volatile UINT8		*)0xFFFFA4)

#define		DADR0			dadr0_addr

/*
 *  D/Aデータレジスタ1
 */
#define		dadr1_addr		(*(volatile UINT8		*)0xFFFFA5)

#define		DADR1			dadr1_addr

/*
 *  D/Aコントロールレジスタ01
 */
#define		dacr_addr		(*(volatile UINT8		*)0xFFFFA6)

#define		DACR			dacr_addr


/********************************************************/
/*  モータコントロールPWMタイマ							*/
/********************************************************/
/*
 *  PWMコントロールレジスタ1
 */
#define		pwcr1_addr		(*(volatile UINT8		*)0xFFFC00)

#define		PWCR1			pwcr1_addr

/*
 *  PWMコントロールレジスタ2
 */
#define		pwcr2_addr		(*(volatile UINT8		*)0xFFFC10)

#define		PWCR2			pwcr2_addr

/*
 *  PWMアウトプットコントロールレジスタ1
 */
#define		pwocr1_addr		(*(volatile UINT8		*)0xFFFC02)

#define		PWOCR1			pwocr1_addr

/*
 *  PWMアウトプットコントロールレジスタ2
 */
#define		pwocr2_addr		(*(volatile UINT8		*)0xFFFC12)

#define		PWOCR2			pwocr2_addr

/*
 *  PWMポラリティレジスタ1
 */
#define		pwpr1_addr		(*(volatile UINT8		*)0xFFFC04)

#define		PWPR1			pwpr1_addr

/*
 *  PWMポラリティレジスタ2
 */
#define		pwpr2_addr		(*(volatile UINT8		*)0xFFFC14)

#define		PWPR2			pwpr2_addr

/*
 *  PWMカウンタ1,2
 */
/*
 *  ※このレジスタはユーザがR/Wができない
 */


/*
 *  PWMサイクルレジスタ1
 */
#define		pwcyr1_addr		(*(volatile UINT16		*)0xFFFC06)

#define		PWCYR1			pwcyr1_addr

/*
 *  PWMサイクルレジスタ2
 */
#define		pwcyr2_addr		(*(volatile UINT16		*)0xFFFC16)

#define		PWCYR2			pwcyr2_addr

/*
 *  PWMデューティレジスタ1A,1C,1E,1G
 */
/*
 *  ※このレジスタはユーザがR/Wができない
 */

/*
 *  PWMバッファレジスタ1
 */
typedef union {
	struct {
		UINT8	dt_high;
		UINT8	dt_low;
	} byte;
	UINT16	word;
} PWBFR1_TYPE;

/*
 *  PWMバッファレジスタ1A
 */
#define		pwbfr1a_addr		(*(volatile PWBFR1_TYPE	*)0xFFFC08)

#define		PWBFR1A				pwbfr1a_addr.word
#define		PWBFR1AH			pwbfr1a_addr.byte.dt_high
#define		PWBFR1AL			pwbfr1a_addr.byte.dt_low

/*
 *  PWMバッファレジスタ1C
 */
#define		pwbfr1c_addr		(*(volatile PWBFR1_TYPE	*)0xFFFC0A)

#define		PWBFR1C				pwbfr1c_addr.word
#define		PWBFR1CH			pwbfr1c_addr.byte.dt_high
#define		PWBFR1CL			pwbfr1c_addr.byte.dt_low

/*
 *  PWMバッファレジスタ1E
 */
#define		pwbfr1e_addr		(*(volatile PWBFR1_TYPE	*)0xFFFC0C)

#define		PWBFR1E				pwbfr1e_addr.word
#define		PWBFR1EH			pwbfr1e_addr.byte.dt_high
#define		PWBFR1EL			pwbfr1e_addr.byte.dt_low

/*
 *  PWMバッファレジスタ1G
 */
#define		pwbfr1g_addr		(*(volatile PWBFR1_TYPE	*)0xFFFC0E)

#define		PWBFR1G				pwbfr1g_addr.word
#define		PWBFR1GH			pwbfr1g_addr.byte.dt_high
#define		PWBFR1GL			pwbfr1g_addr.byte.dt_low

/*
 *  PWMバッファレジスタ2
 */
typedef union {
	struct {
		UINT8	dt_high;
		UINT8	dt_low;
	} byte;
	UINT16	word;
} PWBFR2_TYPE;

/*
 *  PWMバッファレジスタ2A
 */
#define		pwbfr2a_addr		(*(volatile PWBFR2_TYPE	*)0xFFFC18)

#define		PWBFR2A				pwbfr2a_addr.word
#define		PWBFR2AH			pwbfr2a_addr.byte.dt_high
#define		PWBFR2AL			pwbfr2a_addr.byte.dt_low

/*
 *  PWMバッファレジスタ2B
 */
#define		pwbfr2b_addr		(*(volatile PWBFR2_TYPE	*)0xFFFC1A)

#define		PWBFR2B				pwbfr2b_addr.word
#define		PWBFR2BH			pwbfr2a_addr.byte.dt_high
#define		PWBFR2BL			pwbfr2a_addr.byte.dt_low

/*
 *  PWMバッファレジスタ2C
 */
#define		pwbfr2c_addr		(*(volatile PWBFR2_TYPE	*)0xFFFC1C)

#define		PWBFR2C				pwbfr2c_addr.word
#define		PWBFR2CH			pwbfr2a_addr.byte.dt_high
#define		PWBFR2CL			pwbfr2a_addr.byte.dt_low

/*
 *  PWMバッファレジスタ2D
 */
#define		pwbfr2d_addr		(*(volatile PWBFR2_TYPE	*)0xFFFC1E)

#define		PWBFR2D				pwbfr2d_addr.word
#define		PWBFR2DH			pwbfr2a_addr.byte.dt_high
#define		PWBFR2DL			pwbfr2a_addr.byte.dt_low

/*
 *  モジュールストップコントロールレジスタD
 */
#define		mstpcrd_addr		(*(volatile UINT8	*)0xFFFC60)

#define		MSTPCRD				mstpcrd_addr


/********************************************************/
/*  ROM													*/
/********************************************************/
/*
 *  フラッシュメモリコントロールレジスタ1
 */
#define		flmcr1_addr			(*(volatile UINT8	*)0xFFFFA8)

#define		FLMCR1				flmcr1_addr

/*
 *  フラッシュメモリコントロールレジスタ2
 */
#define		flmcr2_addr			(*(volatile UINT8	*)0xFFFFA9)

#define		FLMCR2				flmcr2_addr

/*
 *  消去ブロック指定レジスタ1
 */
#define		ebr1_addr			(*(volatile UINT8	*)0xFFFFAA)

#define		EBR1				ebr1_addr

/*
 *  消去ブロック指定レジスタ2
 */
#define		ebr2_addr			(*(volatile UINT8	*)0xFFFFAB)

#define		EBR2				ebr2_addr

/*
 *  RAMエミュレーションレジスタ
 */
#define		ramer_addr			(*(volatile UINT8	*)0xFFFEDB)

#define		RAMER				ramer_addr

/*
 *  フラッシュメモリパワーコントロールレジスタ
 */
#define		flpwcr_addr			(*(volatile UINT8	*)0xFFFFAC)

#define		FLPWCR				flpwcr_addr


/********************************************************/
/*  クロック発振器										*/
/********************************************************/
/*
 *  システムクロックコントロールレジスタ
 */
#define		sckcr_addr			(*(volatile UINT8	*)0xFFFDE6)

#define		SCKCR				sckcr_addr

/*
 *  ローパワーコントロールレジスタ
 */
#define		lpwrcr_addr			(*(volatile UINT8	*)0xFFFDEC)

#define		LPWRCR				lpwrcr_addr


/********************************************************/
/*  低消費電力状態										*/
/********************************************************/
/*
 *  スタンバイコントロールレジスタ
 */
#define		sbycr_addr		(*(volatile UINT8		*)0xFFFDE4)

#define		SBYCR			sbycr_addr


#endif	/* _SFR_H8S2638_H_ */

