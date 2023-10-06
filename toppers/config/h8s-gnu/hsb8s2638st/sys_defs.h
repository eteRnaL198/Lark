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
 *	ターゲットシステムに依存する定義（hsb8s2638st用）
 */

#ifndef _SYS_DEFS_H_
#define _SYS_DEFS_H_

/* 
 *  カーネルステータスタイプの定義
 *
 *  下記定義を有効にすることで，OSEK仕様の拡張エラーチェックを無効化できる．
 */
/*#define BASIC_STATUS	*/

/* 
 *  ターゲット識別マクロ(システム名の定義)
 */
#define HSB8S2638ST

/*
 *  起動メッセージのターゲットシステム名
 */
#define TARGET_NAME	(const UINT8 *)"H8S/HSB8S2638ST"

/*
 *  割込み番号の定義
 */
#define	INT_NMI			7				/*   7, +0x00001C: 外部割込みNMI		*/
#define	INT_IRQ0		16				/*  16, +0x000040: IRQ0					*/
#define	INT_IRQ1		17				/*  17, +0x000044: IRQ1					*/
#define	INT_IRQ2		18				/*  18, +0x000048: IRQ2					*/
#define	INT_IRQ3		19				/*  19, +0x00004C: IRQ3					*/
#define	INT_IRQ4		20				/*  20, +0x000050: IRQ4					*/
#define	INT_IRQ5		21				/*  21, +0x000054: IRQ5					*/
#define	INT_SWDTEND		24				/*  24, +0x000060: SWDTEND				*/
										/*      (ソフトウェア起動データ転送終了)*/
#define	INT_WOVI0		25				/*  25, +0x000064: WOVI0				*/
										/*      (インターバルタイマ)			*/
#define	INT_PCBRK		27				/*  27, +0x00006C: PCブレーク			*/
#define	INT_ADI			28				/*  28, +0x000070: ADI(A/D変換終了)		*/
#define	INT_WOVI		29				/*  29, +0x000074: WOVI1				*/
										/*      (インターバルタイマ)			*/
#define	INT_TGI0A		32				/*  32, +0x000080: TGI0A				*/
#define	INT_TGI0B		33				/*  33, +0x000084: TGI0B				*/
#define	INT_TGI0C		34				/*  34, +0x000088: TGI0C				*/
#define	INT_TGI0D		35				/*  35, +0x00008C: TGI0D				*/
#define	INT_TCI0V		36				/*  36, +0x000090: TCI0V				*/
#define	INT_TGI1A		40				/*  40, +0x0000A0: TGI1A				*/
#define	INT_TGI1B		41				/*  41, +0x0000A4: TGI1B				*/
#define	INT_TCI1V		42				/*  42, +0x0000A8: TCI1V				*/
#define	INT_TCI1U		43				/*  43, +0x0000AC: TCI1U				*/
#define	INT_TGI2A		44				/*  44, +0x0000B0: TGI2A				*/
#define	INT_TGI2B		45				/*  45, +0x0000B4: TGI2B				*/
#define	INT_TCI2V		46				/*  46, +0x0000B8: TCI2V				*/
#define	INT_TCI2U		47				/*  47, +0x0000BC: TCI2U				*/
#define	INT_TGI3A		48				/*  48, +0x0000C0: TGI3A				*/
#define	INT_TGI3B		49				/*  49, +0x0000C4: TGI3B				*/
#define	INT_TGI3C		50				/*  50, +0x0000C8: TGI3C				*/
#define	INT_TGI3D		51				/*  51, +0x0000CC: TGI3D				*/
#define	INT_TCI3V		52				/*  52, +0x0000D0: TCI3V				*/
#define	INT_TGI4A		56				/*  56, +0x0000E0: TGI4A				*/
#define	INT_TGI4B		57				/*  57, +0x0000E4: TGI4B				*/
#define	INT_TCI4V		58				/*  58, +0x0000E8: TCI4V				*/
#define	INT_TCI4U		59				/*  59, +0x0000EC: TCI4U				*/
#define	INT_TGI5A		60				/*  60, +0x0000F0: TGI5A				*/
#define	INT_TGI5B		61				/*  61, +0x0000F4: TGI5B				*/
#define	INT_TCI5V		62				/*  62, +0x0000F8: TCI5V				*/
#define	INT_TCI5U		63				/*  63, +0x0000FC: TCI5U				*/
#define	INT_ERI0		80				/*  80, +0x000140: ERI0					*/
#define	INT_RXI0		81				/*  81, +0x000144: RXI0					*/
#define	INT_TXI0		82				/*  82, +0x000148: TXI0					*/
#define	INT_TEI0		83				/*  83, +0x00014C: TEI0					*/
#define	INT_ERI1		84				/*  84, +0x000150: ERI1					*/
#define	INT_RXI1		85				/*  85, +0x000154: RXI1					*/
#define	INT_TXI1		86				/*  86, +0x000158: TXI1					*/
#define	INT_TEI1		87				/*  87, +0x00015C: TEI1					*/
#define	INT_ERI2		88				/*  88, +0x000160: ERI2					*/
#define	INT_RXI2		89				/*  89, +0x000164: RXI2					*/
#define	INT_TXI2		90				/*  90, +0x000168: TXI2					*/
#define	INT_TEI2		91				/*  91, +0x00016C: TEI2					*/
#define	INT_I2CI0		100				/* 100, +0x000190: I2Cチャンネル0		*/
#define	INT_DDCSW1		101				/* 101, +0x000194: フォーマットスイッチ	*/
#define	INT_I2CI1		102				/* 102, +0x000198: I2Cチャンネル1		*/
#define	INT_PWM1		104				/* 104, +0x0001A0: PWM1					*/
#define	INT_PWM2		105				/* 105, +0x0001A4: PWM2					*/
#define	INT_HCAN1_RM1	106				/* 106, +0x0001A8: HCAN1 RM1			*/
#define	INT_HCAN1_RM0	107				/* 107, +0x0001AC: HCAN1 RM0			*/
#define	INT_HCAN0_RM1	108				/* 108, +0x0001B0: HCAN0 RM1			*/
#define	INT_HCAN0_RM0	109				/* 109, +0x0001B4: HCAN0 RM0			*/


#endif /* _SYS_DEFS_H_ */
