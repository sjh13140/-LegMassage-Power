#ifndef __TM52FN8276_SFR_CONFIG_H__
#define __TM52FN8276_SFR_CONFIG_H__


#define P0_MASK					(0xff)

/*---- PCON ----*/
#define	PCON_MASK				(0xff)

#define PCON_IDL_MASK			(0x01)
#define PCON_IDL_POS			(0)
#define PCON_PD_MASK			(0x02)
#define PCON_PD_POS				(1)
#define PCON_GF0_MASK			(0x04)
#define PCON_GF0_POS			(2)
#define PCON_GF1_MASK			(0x08)
#define PCON_GF1_POS			(3)
#define PCON_SMOD_MASK			(0x80)
#define PCON_SMOD_POS			(7)

/*---- TCON ----*/
#define TCON_MASK				(0xff)


/*---- TMOD ----*/
#define TMOD_MASK				(0xff)
#define TMOD_TMOD0_MASK			(0x03)
#define TMOD_TMOD0_POS			(0)
#define TMOD_CT0N_MASK			(0x04)
#define TMOD_CT0N_POS			(2)
#define TMOD_GATE0_MASK			(0x08)
#define TMOD_GATE0_POS			(3)
#define TMOD_TMOD1_MASK			(0x30)
#define TMOD_TMOD1_POS			(4)
#define TMOD_CT1N_MASK			(0x40)
#define TMOD_CT1N_POS			(6)
#define TMOD_GATE1_MASK			(0x80)
#define TMOD_GATE1_POS			(7)


//TL0
#define TL0_MASK				(0xff)
#define TL0_TL0_MASK			(0xff)
#define TL0_TL0_POS				(0)


//TL1
#define TL1_MASK				(0xff)
#define TL1_TL1_MASK			(0xff)
#define TL1_TL1_POS				(0)


//TH0
#define TH0_MASK				(0xff)
#define TH0_TH0_MASK			(0xff)
#define TH0_TH0_POS				(0)

//TH1
#define TH1_MASK				(0xff)
#define TH1_TH1_MASK			(0xff)
#define TH1_TH1_POS				(0)


//SCON2
#define SCON2_MASK				(0xff)
#define SCON2_RI2_MASK			(0x01)
#define SCON2_RI2_POS			(0)
#define SCON2_TI2_MASK			(0x02)
#define SCON2_TI2_POS			(1)
#define SCON2_RB82_MASK			(0x04)
#define SCON2_RB82_POS			(2)
#define SCON2_TB82_MASK			(0x08)
#define SCON2_TB82_POS			(3)
#define SCON2_REN2_MASK			(0x10)
#define SCON2_REN2_POS			(4)
#define SCON2_SM_MASK			(0x80)
#define SCON2_SM_POS			(7)

//P0OE
#define P0OE_MASK				(0xff)
#define P0OE_P0OE0_MASK			(0x01)
#define P0OE_P0OE0_POS			(0)
#define P0OE_P0OE1_MASK			(0x02)
#define P0OE_P0OE1_POS			(1)
#define P0OE_P0OE2_MASK			(0x04)
#define P0OE_P0OE2_POS			(2)
#define P0OE_P0OE3_MASK			(0x08)
#define P0OE_P0OE3_POS			(3)
#define P0OE_P0OE4_MASK			(0x10)
#define P0OE_P0OE4_POS			(4)
#define P0OE_P0OE5_MASK			(0x20)
#define P0OE_P0OE5_POS			(5)
#define P0OE_P0OE6_MASK			(0x40)
#define P0OE_P0OE6_POS			(6)
#define P0OE_P0OE7_MASK			(0x80)
#define P0OE_P0OE7_POS			(7)


//P0LOE
#define P0LOE_MASK				(0xff)
#define P0LOE_P0LOE_MASK		(0xff)
#define P0LOE_P0LOE_POS			(0)
//////////////////////////////////////////

//P2MOD
#define P2MOD_MASK				(0xff)
#define P2MOD_P2MOD0_MASK		(0x03)
#define P2MOD_P2MOD0_POS		(0)
#define P2MOD_P2MOD1_MASK		(0x0c)
#define P2MOD_P2MOD1_POS		(2)

//OPTION
#define OPTION_MASK				(0xff)
#define OPTION_ADCKS_MASK		(0x0c)
#define OPTION_ADCKS_POS		(2)
#define OPTION_WDTPSC_MASK		(0x30)
#define OPTION_WDTPSC_POS		(4)
#define OPTION_UART1W_MASK		(0x80)
#define OPTION_UART1W_POS		(7)

//INTFLG
#define INTFLG_MASK				(0xff)
#define INTFLG_TF3_MASK			(0x01)
#define INTFLG_TF3_POS			(0)
#define INTFLG_P1IF_MASK		(0x02)
#define INTFLG_P1IF_POS			(1)
#define INTFLG_IE2_MASK			(0x04)
#define INTFLG_IE2_POS			(2)
#define INTFLG_ADIF_MASK		(0x10)
#define INTFLG_ADIF_POS			(4)
#define INTFLG_TKIF_MASK		(0x20)
#define INTFLG_TKIF_POS			(5)

//P1WKP
#define P1WKUP_MASK				(0xff)
#define P1WKUP_P1WKUP_MASK		(0xff)
#define P1WKUP_P1WKUP_POS		(0)

//SWCMD
#define SWCMD_MASK				(0xff)///!!!

//SCON
#define SCON_MASK				(0xff)

//SBUF
#define SBUF_MASK				(0xff)
#define SBUF_SBUF_MASK			(0xff)
#define SBUF_SBUF_POS			(0)

//PWM0PRD
#define PWM0PRD_MASK			(0xff)
#define PWM0PRD_PWM0PRD_MASK	(0xff)
#define PWM0PRD_PWM0PRD_POS		(0)

//PWM0DH
#define PWM0DH_MASK				(0xff)
#define PWM0DH_PWM0DH_MASK		(0xff)
#define PWM0DH_PWM0DH_POS		(0)

//PWM1PRD
#define PWM1PRD_MASK			(0xff)
#define PWM1PRD_PWM1PRD_MASK	(0xff)
#define PWM1PRD_PWM1PRD_POS		(0)

//PWM1DH
#define PWM1DH_MASK				(0xff)
#define PWM1DH_PWM1DH_MASK		(0xff)
#define PWM1DH_PWM1DH_POS		(0)

//PWM2PRD
#define PWM2PRD_MASK			(0xff)
#define PWM2PRD_PWM2PRD_MASK	(0xff)
#define PWM2PRD_PWM2PRD_POS		(0)

//PWM2DH
#define PWM2DH_MASK				(0xff)
#define PWM2DH_PWM2DH_MASK		(0xff)
#define PWM2DH_PWM2DH_POS		(0)

//P2
#define P2_MASK					(0xff)

//PWMCON
#define PWMCON_MASK				(0xff)
#define PWMCON_PWM0DL_MASK		(0x03)
#define PWMCON_PWM0DL_POS		(0)
#define PWMCON_PWM0CKS_MASK		(0x0c)
#define PWMCON_PWM0CKS_POS		(2)
#define PWMCON_PWM1DL_MASK		(0x30)
#define PWMCON_PWM1DL_POS		(4)
#define PWMCON_PWM1CKS_MASK		(0xc0)
#define PWMCON_PWM1CKS_POS		(6)

//P1MODL
#define P1MODL_MASK				(0xff)
#define P1MODL_P1MOD0_MASK		(0x03)
#define P1MODL_P1MOD0_POS		(0)
#define P1MODL_P1MOD1_MASK		(0x0c)
#define P1MODL_P1MOD1_POS		(2)
#define P1MODL_P1MOD2_MASK		(0x30)
#define P1MODL_P1MOD2_POS		(4)
#define P1MODL_P1MOD3_MASK		(0xc0)
#define P1MODL_P1MOD3_POS		(6)

//P1MODH
#define P1MODH_MASK				(0xff)
#define P1MODH_P1MOD4_MASK		(0x03)
#define P1MODH_P1MOD4_POS		(0)
#define P1MODH_P1MOD5_MASK		(0x0c)
#define P1MODH_P1MOD5_POS		(2)
#define P1MODH_P1MOD6_MASK		(0x30)
#define P1MODH_P1MOD6_POS		(4)
#define P1MODH_P1MOD7_MASK		(0xc0)
#define P1MODH_P1MOD7_POS		(6)


//P3MODL
#define P3MODL_MASK				(0xff)
#define P3MODL_P3MOD0_MASK		(0x03)
#define P3MODL_P3MOD0_POS		(0)
#define P3MODL_P3MOD1_MASK		(0x0c)
#define P3MODL_P3MOD1_POS		(2)
#define P3MODL_P3MOD2_MASK		(0x30)
#define P3MODL_P3MOD2_POS		(4)
#define P3MODL_P3MOD3_MASK		(0xc0)
#define P3MODL_P3MOD3_POS		(6)

//P3MODH
#define P3MODH_MASK				(0xff)
#define P3MODH_P3MOD4_MASK		(0x03)
#define P3MODH_P3MOD4_POS		(0)
#define P3MODH_P3MOD5_MASK		(0x0c)
#define P3MODH_P3MOD5_POS		(2)
#define P3MODH_P3MOD6_MASK		(0x30)
#define P3MODH_P3MOD6_POS		(4)
#define P3MODH_P3MOD7_MASK		(0xc0)
#define P3MODH_P3MOD7_POS		(6)


//PINMOD
#define PINMOD_MASK				(0xff)
#define PINMOD_T0OE_MASK		(0x01)
#define PINMOD_T0OE_POS			(0)
#define PINMOD_HSNK0EN_MASK  (0X02)
#define PINMOD_HSNK0EN_POS	(1)
#define PINMOD_HSNK1EN_MASK  (0X04)
#define PINMOD_HSNK1EN_POS	(2)
#define PINMOD_HSNK2EN_MASK  (0X08)
#define PINMOD_HSNK2EN_POS	(3)
#define PINMOD_T2OE_MASK		(0x10)
#define PINMOD_T2OE_POS			(4)
#define PINMOD_TCOE_MASK		(0x20)
#define PINMOD_TCOE_POS			(5)
#define PINMOD_PWM0OE_MASK		(0x40)
#define PINMOD_PWM0OE_POS		(6)
#define PINMOD_PWM1OE_MASK		(0x80)
#define PINMOD_PWM1OE_POS		(7)


//PWMCON2
#define PWMCON2_MASK			(0xff)
#define PWMCON2_PWM2DL_MASK		(0x03)
#define PWMCON2_PWM2DL_POS		(0)
#define PWMCON2_PWM2CKS_MASK	(0x0c)
#define PWMCON2_PWM2CKS_POS		(2)
#define PWMCON2_PWM2OE_MASK		(0x10)
#define PWMCON2_PWM2OE_POS		(4)

//IE
#define IE_MASK					(0xff)


//INTE1
#define INTE1_MASK				(0xff)
#define INTE1_TM3IE_MASK		(0x01)
#define INTE1_TM3IE_POS			(0)
#define INTE1_P1IE_MASK			(0x02)
#define INTE1_P1IE_POS			(1)
#define INTE1_EX2_MASK			(0x04)
#define INTE1_EX2_POS			(2)
#define INTE1_ADTKIE_MASK		(0x08)
#define INTE1_ADTKIE_POS		(3)
#define INTE1_SPIE_MASK			(0x10)
#define INTE1_SPIE_POS			(4)
#define INTE1_ES2_MASK			(0x20)
#define INTE1_ES2_POS			(5)


//ADTKDT
#define ADTKDT_MASK				(0xff)
#define ADTKDT_TKDH_MASK		(0x0f)
#define ADTKDT_TKDH_POS			(0)
#define ADTKDT_ADCDL_MASK		(0xf0)
#define ADTKDT_ADCDL_POS		(4)

//ADCSH
#define ADCDH_MASK				(0xff)
#define ADCDH_ADCDH_MASK		(0xff)
#define ADCDH_ADCDH_POS			(0)


//TKDL
#define TKDL_MASK				(0xff)
#define TKDL_TKDL_MASK			(0xff)
#define TKDL_TKDL_POS			(0)


//TKFREQ
#define TKFREQ_MASK				(0xff)
#define TKFREQ_TKFREQ_MASK		(0x7f)
#define TKFREQ_TKFREQ_POS		(0)

//TKCON
#define TKCON_MASK				(0xff)
#define TKCON_TKCHS_MASK		(0x1f)
#define TKCON_TKCHS_POS			(0)
#define TKCON_TKIVCS_MASK		(0X20)
#define TKCON_TKIVCS_POS		(5)
#define TKCON_TKEOC_MASK		(0x40)
#define TKCON_TKEOC_POS			(6)
#define TKCON_TKPD_MASK			(0x80)
#define TKCON_TKPD_POS			(7)

//P0ADIE
#define P0ADIE_MASK				(0xff)
#define P0ADIE_P0ADIE_MASK		(0xf0)
#define P0ADIE_P0ADIE_POS		(4)


//LEDCON
#define LEDCON_MASK				(0xff)
#define LEDCON_LEDBRIT_MASK		(0x07)
#define LEDCON_LEDBRIT_POS		(0)
#define LEDCON_LEDHOLD_MASK		(0x08)
#define LEDCON_LEDHOLD_POS		(3)
#define LEDCON_LEDPSC_MASK		(0x30)
#define LEDCON_LEDPSC_POS		(4)
#define LEDCON_LEDEN_MASK		(0xc0)
#define LEDCON_LEDEN_POS		(6)

//LEDCON2
#define LEDCON2_MASK			(0xff)
#define LEDCON2_LEDBRIT1_MASK	(0x07)
#define LEDCON2_LEDBRIT1_POS	(0)
#define LEDCON2_LEDBRIT2_MASK	(0x70)
#define LEDCON2_LEDBRIT2_POS	(4)
#define LEDCON2_LEDSMDIS_MASK	(0x80)
#define LEDCON2_LEDSMDIS_POS	(7)


//TKTMRL
#define TKTMRL_MASK				(0xff)
#define TKTMRL_TKTMRL_MASK		(0xff)
#define TKTMRL_TKTMRL_POS		(0)


//TKCON2
#define TKCON2_MASK				(0xff)
#define TKCON2_TKTMRH_MASK		(0x0f)
#define TKCON2_TKTMRH_POS		(0)
#define TKCON2_JMPVAL_MASK		(0x30)
#define TKCON2_JMPVAL_POS		(4)
#define TKCON2_TKFREQS_MASK		(0X40)
#define TKCON2_TKFREQS_POS		(6)
#define TKCON2_TKFJMP_MASK		(0x80)
#define TKCON2_TKFJMP_POS		(7)


//ADCHS
#define ADCHS_MASK				(0xff)
#define ADCHS_ADCHS_MASK		(0x0f)
#define ADCHS_ADCHS_POS			(0)

#define IP_MASK					(0xff)

//IPH
#define IPH_MASK				(0xff)
#define IPH_PX0H_MASK			(0x01)
#define IPH_PX0H_POS			(0)
#define IPH_PT0H_MASK			(0x02)
#define IPH_PT0H_POS			(1)
#define IPH_PX1H_MASK			(0x04)
#define IPH_PX1H_POS			(2)
#define IPH_PT1H_MASK			(0x08)
#define IPH_PT1H_POS			(3)
#define IPH_PSH_MASK			(0x10)
#define IPH_PSH_POS				(4)
#define IPH_PT2H_MASK			(0x20)
#define IPH_PT2H_POS			(5)


//IP1
#define IP1_MASK				(0xff)
#define IP1_PT3_MASK			(0x01)
#define IP1_PT3_POS				(0)
#define IP1_PP1_MASK			(0x02)
#define IP1_PP1_POS				(1)
#define IP1_PX2_MASK			(0x04)
#define IP1_PX2_POS				(2)
#define IP1_PADTKI_MASK			(0x08)
#define IP1_PADTKI_POS			(3)
#define IP1_PSPI_MASK			(0x10)
#define IP1_PSPI_POS			(4)
#define IP1_PS2_MASK			(0x20)
#define IP1_PS2_POS				(5)


//IP1H
#define IP1H_MASK				(0xff)
#define IP1H_PT3H_MASK			(0x01)
#define IP1H_PT3H_POS			(0)
#define IP1H_PP1H_MASK			(0x02)
#define IP1H_PP1H_POS			(1)
#define IP1H_PX2H_MASK			(0x04)
#define IP1H_PX2H_POS			(2)
#define IP1H_PADTKIH_MASK		(0x08)
#define IP1H_PADTKIH_POS		(3)
#define IP1H_PSPIH_MASK			(0x10)
#define IP1H_PSPIH_POS			(4)
#define IP1H_PS2H_MASK			(0x20)
#define IP1H_PS2H_POS			(5)

//SPCON
#define SPCON_MASK				(0xff)
#define SPCON_SPCR_MASK			(0x03)
#define SPCON_SPCR_POS			(0)
#define SPCON_LSBF_MASK			(0x04)
#define SPCON_LSBF_POS			(2)
#define SPCON_SSDIS_MASK		(0x08)
#define SPCON_SSDIS_POS			(3)
#define SPCON_CPHA_MASK			(0x10)
#define SPCON_CPHA_POS			(4)
#define SPCON_CPOL_MASK			(0x20)
#define SPCON_CPOL_POS			(5)
#define SPCON_MSTR_MASK			(0x40)
#define SPCON_MSTR_POS			(6)
#define SPCON_SPEN_MASK			(0x80)
#define SPCON_SPEN_POS			(7)


//SPSTA
#define SPSTA_MASK				(0xff)
#define SPSTA_SPBSY_MASK		(0x04)
#define SPSTA_SPBSY_POS			(2)
#define SPSTA_RCVBF_MASK		(0x08)
#define SPSTA_RCVBF_POS			(3)
#define SPSTA_RCVOVF_MASK		(0x10)
#define SPSTA_RCVOVF_POS		(4)
#define SPSTA_MODF_MASK			(0x20)
#define SPSTA_MODF_POS			(5)
#define SPSTA_WCOL_MASK			(0x40)
#define SPSTA_WCOL_POS			(6)
#define SPSTA_SPIF_MASK			(0x80)
#define SPSTA_SPIF_POS			(7)

//SPDAT
#define SPDAT_MASK				(0xff)
#define SPDAT_SPDAT_MASK		(0xff)
#define SPDAT_SPDAT_POS			(0)


//T2CON
#define T2CON_MASK				(0xff)

//IAPWE
#define IAPWE_MASK				(0xff)//!!!

//RCP2L
#define RCP2L_MASK				(0xff)
#define RCP2L_RCP2L_MASK		(0xff)
#define RCP2L_RCP2L_POS			(0)


//RCP2H
#define RCP2H_MASK				(0xff)
#define RCP2H_RCP2H_MASK		(0xff)
#define RCP2H_RCP2H_POS			(0)


//TL2
#define TL2_MASK				(0xff)
#define TL2_TL2_MASK			(0xff)
#define TL2_TL2_POS				(0)


//TH2
#define TH2_MASK				(0xff)
#define TH2_TH2_MASK			(0xff)
#define TH2_TH2_POS				(0)


//P1LOE
#define P1LOE_MASK				(0xff)
#define P1LOE_P1LOE_MASK		(0xff)
#define P1LOE_P1LOE_POS			(0)


//P2LOE
#define P2LOE_MASK				(0xff)
#define P2LOE_P2LOE_MASK		(0x03)
#define P2LOE_P2LOE_POS			(0)


//P3LOE
#define P3LOE_MASK				(0xff)
#define P3LOE_P3LOE_MASK		(0xff)
#define P3LOE_P3LOE_POS			(0)


//CLKCON
#define CLKCON_MASK				(0xff)

//EFTCON
#define EFTCON_MASK				(0XFF)
#define EFTCON_CKHLDE_MASK		(0X01)
#define EFTCON_CKHLDE_POS		(0)
#define EFTCON_EFTWOUT_MASK		(0X02)
#define EFTCON_EFTWOUT_POS		(1)
#define EFTCON_EFTWCPU_MASK		(0X04)
#define EFTCON_EFTWCPU_POS		(2)
#define EFTCON_EFTSLOW_MASK		(0X08)
#define EFTCON_EFTSLOW_POS		(3)
#define EFTCON_EFT1S_MASK		(0X30)
#define EFTCON_EFT1S_POS		(4)
#define EFTCON_EFT1CS_MASK		(0X40)
#define EFTCON_EFT1CS_POS		(6)
#define EFTCON_EFT2CS_MASK		(0X80)
#define EFTCON_EFT2CS_POS		(7)

//AUX3
#define AUX3_MASK				(0xff)
#define AUX3_ADCVREFS_MASK		(0x01)
#define AUX3_ADCVREFS_POS		(0)
#define AUX3_VBGEN_MASK			(0x4)
#define AUX3_VBGEN_POS			(2)
#define AUX3_TM3PSC_MASK		(0x38)
#define AUX3_TM3PSC_POS			(3)

//CRCDL
#define CRCDL_MASK				(0xff)
#define CRCDL_CRCDL_MASK		(0xff)
#define CRCDL_CRCDL_POS			(0)


//CRCDH
#define CRCDH_MASK				(0xff)
#define CRCDH_CRCDH_MASK		(0xff)
#define CRCDH_CRCDH_POS			(0)

//CRCIN
#define CRCIN_MASK				(0xff)
#define CRCIN_CRCIN_MASK		(0xff)
#define CRCIN_CRCIN_POS			(0)


//CFGBG
#define CFGBG_MASK				(0xff)
#define CFGBG_BGTRIM_MASK		(0x1f)
#define CFGBG_BGTRIM_POS		(0)


//CFGWL
#define CFGWL_MASK				(0xff)
#define CFGWL_FRCF_MASK			(0x7f)
#define CFGWL_FRCF_POS			(0)


//AUX2
#define AUX2_MASK				(0xff)
#define AUX2_LVRPD_MASK			(0x01)
#define AUX2_LVRPD_POS			(0)
#define AUX2_IAPTE_MASK			(0x06)
#define AUX2_IAPTE_POS			(1)
#define AUX2_VBGOUT_MASK		(0x10)
#define AUX2_VBGOUT_POS			(4)
#define AUX2_PWRSAV_MASK		(0x20)
#define AUX2_PWRSAV_POS			(5)
#define AUX2_WDTE_MASK			(0xc0)
#define AUX2_WDTE_POS			(6)


#define		PIN_MODE_OD 	  	        0x01    //开漏（可设高阻）
#define		PIN_MODE_OD_IPU 	  	    0x00    //开漏（可设上拉）
#define		PIN_MODE_PP		            0x02    //推挽输出
#define		PIN_P0MODE_OD		          0x00    //P0口输入
#define		PIN_P0MODE_PP		          0x01    //P0口推挽输出
#define		PIN_P2MOD0_OD		          0x03    //P20晶振输入
#define		PIN_P2MOD1_OD	            0x03    //P21晶振输入
#define		PIN_MODE_AD		            0x03    //AD输入
#define   PIN_MODE_AF0              0x01    //PWM0
#define   PIN_MODE_AF1              0x01    //PWM1
#define   PIN_MODE_AF2              0x01    //PWM2




//AUX1
#define AUX1_MASK				(0xff)


#define SET_REG_BITS(reg,regbit,value) ((reg) = (reg)&~(reg##_##regbit##_##MASK) | ((value) << (reg##_##regbit##_##POS)))               //设置多位寄存器

#define	CLEAR_REG_BITS(reg,regbit) ((reg) = (reg)&~(reg##_##regbit##_##MASK))                                                           //清除寄存器当前状态

#define SET_REG(reg,value)	((reg) = (value))                                                                                           //设置一位寄存器
#define GET_REG(reg)		(reg)

#endif