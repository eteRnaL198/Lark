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
;  Copyright (C) 2006 by Witz Corporation, JAPAN
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
;  ターゲットシステム依存モジュール アセンブリ言語部（hsb8s2638st用）
;
	.h8300s

	.section .text
	.align 2

#define	SYSCR	0xFFFDE5
#define	SCKCR	0xFFFDE6
#define	ABWCR	0xFFFED0
#define	ASTCR	0xFFFED1
#define	WCRH	0xFFFED2
#define	WCRL	0xFFFED3
#define	BCRH	0xFFFED4
#define	BCRL	0xFFFED5
#define	PFCR	0xFFFDEB
#define	PCDDR	0xFFFE3B

;
;  低レベルのターゲットシステム依存の初期化
;
;  スタートアップモジュールの中で，スタック初期化の後に呼び出される．
;
	.global	hardware_init_hook

;
;  低レベルのソフトウェア依存の初期化
;
;  スタートアップモジュールの中で，ユーザメイン関数呼び出しの前に
;  呼び出される．
;
	.global	software_init_hook

	.section .text
	.align 1

;
;  hardware_init_hookを無効にする場合は下記.equ 定義をコメントアウトし，
;  関数の記述を削除すること．
;
;  .equ	hardware_init_hook,	0x00000000
hardware_init_hook:

	;
	;  CCR の初期化
	;  ・割込み制御モード0 における割込み禁止 (I = 1 ; CCR)
	;
	ldc.b	#0x80, ccr

	;
	;  EXR の初期化
	;  ・割込み制御モード2 における割込み禁止 (I2, I1, I0 = 1 ; CCR)
	;
	ldc.b	#0x07, exr

	;
	;  動作モード設定
	;  ・CPU動作モードはハードウェアにて設定
	;    拡張メモリ有り：モード6
	;    拡張メモリ無し：モード7(モード6でも動作可能(一部ポートが外部バスとなる))
	;      モード切替方法
	;        HSB8S2638Q:J7のショートにてモード6,フリーにてモード7
	;        HSB8S2638ST:DIP SW2の1(MD0)ONにてモード6,OFFにてモード7
	;  ・割込み制御モード2(EXRのI0〜I2でマスク制御)
	;  ・内部RAM使用
	;  ・動作クロック20MHz fx/1
	;
	mov.b	#0x21, r0l
	mov.b	r0l, @SYSCR
	mov.b	#0x00, r0l
	mov.b	r0l, @SCKCR

	;
	;  データバスの設定
	;  ・エリア1(SRAM)を16ビット幅に設定
	;  ・全エリア3ステートのウェイト
	;  ・エリア7,6,5,4のプログラムウェイトは3ステート
	;  ・エリア3,2,1,0のプログラムウェイトは3ステート
	;  ・異なるエリアのリードサイクル連続時アイドルサイクル挿入
	;  ・リードサイクル/ライトサイクル連続時アイドルサイクル挿入
	;  ・エリア0は基本バスインタフェイス
	;  ・ライトデータバッファ機能無効
	;  ・A8〜A23出力許可
	;
#if defined(USE_EXT_RAM)
	mov.b	#0xfd, r1l
	mov.b	r1l, @ABWCR
	mov.b   #0xff, r1l
	mov.b   r1l, @ASTCR
	mov.b   #0xff, r1l
	mov.b   r1l, @WCRH
	mov.b   #0xff, r1l
	mov.b   r1l, @WCRL
	mov.b   #0xd0, r1l
	mov.b   r1l, @BCRH
	mov.b   #0x08, r1l
	mov.b   r1l, @BCRL
	mov.b	#0x0f, r0l
	mov.b	r0l, @PFCR

	;
	;  拡張メモリ使用時のポート設定
	;  ・アドレスバスP10-13,PA,PBはPFCRの設定に依存するため設定不要
	;  ・アドレスバスPCはDDR=1にてアドレス出力
	;  ・データバスPDはモード6では常にデータ入出力のため設定不要
	;  ・データバスPEはABWCRの設定に依存するため設定不要
	;  ・制御バスPF3-PF6はABWCRおよびPFCRの設定に依存するため設定不要
	;
	mov.b	#0xff, r1l
	mov.b	r1l, @PCDDR
#endif	; USE_EXT_RAM

	rts

;
;  software_init_hookを有効にする場合は下記.equ 定義をコメント化し，
;  関数シンボルのコメントアウトと関数内部の記述を行うこと．
;
	.equ software_init_hook,	0x00000000
;software_init_hook:
;	rts


