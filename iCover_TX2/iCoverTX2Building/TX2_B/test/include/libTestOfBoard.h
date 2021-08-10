#ifndef _LIBTESTOFBOARD_
#define _LIBTESTOFBOARD_

#define MAC_SIZE 18
#define IP_SIZE	16

/****************************************
 *
 * Error code
 *
 ****************************************/
enum ERROR_CODE{
	OK,
	INVALID_ARG,
	FAILED,
	NOT_FOUND_DEVICE,
};

/****************************************
 *
 * Device information
 *
 ****************************************/
typedef struct tagDEVINFO_RESULT{
	char *pszModule;
	char *pszCarrierBoard;
	char *pszSerialNumber;
	char *pszMAC_Address;
	char *pszBSP_Version;
	char *pszDTS_Name;
}DEVINFO_RESULT;

/****************************************
 *
 * LAN Testing
 *
 ****************************************/
typedef struct tagLAN_CFG{
	int		nLAN_ID;
}LAN_CFG;

typedef struct tagLAN_Result{
	int 				nResult;
	char 				szIP[IP_SIZE];
}LAN_RESULT;

/****************************************
 *
 * WIFI Testing
 *
 ****************************************/
typedef struct tagWIFI_Result{
	int 				nResult;
	char				szMACNum[MAC_SIZE];
}WIFI_RESULT;

/****************************************
 *
 * Bluetooth Testing
 *
 ****************************************/
typedef struct tagBT_Result{
	int 				nResult;
	char 				szMACNum[MAC_SIZE];
}BT_RESULT;

/****************************************
 *
 * SDCARD Testing
 *
 ****************************************/
typedef struct tagSDCARD_CFG{
	char 	*pszDevPath;
	char 	*pszTemp_path;
	char 	*pszTemp_file;
}SDCARD_CFG;

typedef struct tagSDCARD_Result{
	int 				nResult;
	unsigned long long 	nTimeCost_ms;
	unsigned int 		nTransferSpeed;
}SDCARD_RESULT;

/****************************************
 *
 * mSATA Testing
 *
 ****************************************/
typedef struct tagMSATA_CFG{
	char    *pszTemp_path;
	char    *pszTemp_file;
}MSATA_CFG;

typedef struct tagMSATA_Result{
	int                     nResult;
	unsigned long long      nTimeCost_ms;
	unsigned int            nTransferSpeed;
}MSATA_RESULT;

/****************************************
 *
 * mPCIE Testing
 *
 ****************************************/
enum MPCIE_Type{
	STANDARD,
	HYBRID
};

typedef struct tagMPCIE_CFG{
        int nMPCIE_type;
}MPCIE_CFG;

typedef struct tagMPCIE_Result{
        int nResult;
}MPCIE_RESULT;

/****************************************
 *
 * RS232 Testing
 *
 ****************************************/
typedef struct tagRS232_CFG{
	char	*pszDevName;
	char	*pszTestingData;
}RS232_CFG;

typedef struct tagRS232_RESULT{
	int		nResult;
}RS232_RESULT;

/****************************************
 *
 * GPIO Testing
 *
 ****************************************/
typedef struct tagGPIO_CFG{
	int		nGPIO_Pins_Number;
	int		*pGPIO_Pins;
}GPIO_CFG;

typedef struct tagGPIO_RESULT{
	int		*nResults;
}GPIO_RESULT;

/****************************************
 *
 * UART Testing
 *
 ****************************************/
typedef struct tagUART_CFG{
	char	*pszDevName;
	char	*pszTestingData;
}UART_CFG;

typedef struct tagUART_RESULT{
	int		nResult;
}UART_RESULT;

/****************************************
 *
 * FAN Testing
 *
 ****************************************/
typedef struct tagFAN_CFG{
	int 	nValue;
}FAN_CFG;

typedef struct tagFAN_RESULT{
	int		nResult;
}FAN_RESULT;

/****************************************
 *
 * CSI Testing
 *
 ****************************************/

/****************************************
 *
 * CANBus Testing
 *
 ****************************************/
typedef struct tagCAN_CFG{
	char	*pszSendCAN;
	char	*pszReceiveCAN;
	char 	*pszId;
	char	*pszData;
}CAN_CFG;

typedef struct tagCAN_RESULT{
	int 	nResult;
}CAN_RESULT;

/****************************************
 *
 * I2C Testing
 *
 ****************************************/
typedef struct tagI2C_CFG{
	int		nI2C_ID;
	int		nAddress;
	int		nData;
}I2C_CFG;

typedef struct tagI2C_RESULT{
	int		nResult;
}I2C_RESULT;

/****************************************
 *
 * SPI Testing
 *
 ****************************************/
typedef struct tagSPI_CFG{
	char*	pszDeviceName;
	char*	pszData;
	int		nDatalength;
}SPI_CFG;

typedef struct tagSPI_RESULT{
	int nResult;
}SPI_RESULT;

/****************************************
 *
 * SENSORS Testing
 *
 ****************************************/
enum SENSORS_TYPE{
	TEMPERATURE,
};

typedef struct tagSENSORS_CFG{
	int nType;
}SENSORS_CFG;

typedef struct tagSENSORS_RESULT{
	int nResult;
}SENSORS_RESULT;

/****************************************
 *
 * USB Testing
 *
 ****************************************/
enum USB_PORT_POSITION{
	UP,
	DOWN
};

enum INTERFACE_TYPE{
	USB_3_0_TYPE_A,
	USB_3_0_TYPE_C,
	MICRO_USB
};

enum USB_Type{
	USB_2_0,
	USB_3_0
};

typedef struct tagUSB_CFG{
	int	nInterfaceType;
	char *pUSB_3_0_TYPE_A_UP_USB3DEV;
	char *pUSB_3_0_TYPE_A_UP_USB2DEV;
	char *pUSB_3_0_TYPE_A_DOWN_USB3DEV;
	char *pUSB_3_0_TYPE_A_DOWN_USB2DEV;
	char *pUSB_3_0_TYPE_C_USB3DEV;
	char *pUSB_3_0_TYPE_C_USB2DEV;
	char *pMICRO_USB_DEV;
}USB_CFG;

typedef struct tagUSB_RESULT{
	int					nResultNum;
	int 				*pResult;
	int					*pUSBType;
	int					*pPortPosition;
	unsigned long long 	*pTimeCost_ms;
	unsigned int 		*pTransferSpeed;
}USB_RESULT;

/****************************************
 *
 * M.2 M Key Testing
 *
 ****************************************/
typedef struct tagM2_MKEY_RESULT{
	int 				nResult;
	unsigned long long 	nTimeCost_ms;
	unsigned int 		nTransferSpeed;
}M2_MKEY_RESULT;

/****************************************
 *
 * M.2 E Key Testing
 *
 ****************************************/
typedef struct tagM2_EKEY_CFG{
	char *pszKeyword;
}M2_EKEY_CFG;

typedef struct tagM2_EKEY_RESULT{
	int nResult;
}M2_EKEY_RESULT;

/****************************************
 *
 * EEPROM Testing
 *
 ****************************************/

#define EEPROM_SIZE 88

enum EEPROM_ACTION{
	WRITE_EEPROM,
	READ_EEPROM,
};

typedef struct tagEEPROM_CFG{
	int	nI2C_ID;
	int nAddress;
	char *pszContent;
}EEPROM_CFG;

typedef struct tagEEPROM_Result{
	int nResult;
}EEPROM_Result;

/****************************************
 *
 * APIs of Library
 *
 ****************************************/
typedef void (*CALLBACK_LOG_FUNC)(char *szMsg);

#ifdef __cplusplus
extern "C"{	
	void 		TOB_GetLibVersion(char *szVersion);
	void		TOB_SetLogFunc(CALLBACK_LOG_FUNC func);
	void 		TOB_GetDeviceInfo(DEVINFO_RESULT *devinfo_result);
	int			TOB_LAN_testing(LAN_CFG *lan_cfg, LAN_RESULT *lan_result);
	int			TOB_WIFI_testing(WIFI_RESULT *wifi_result);
	int			TOB_BT_testing(BT_RESULT *bt_result);
	int			TOB_SDCARD_testing(SDCARD_CFG *sdcard_cfg, SDCARD_RESULT *sdcard_result);
	int			TOB_MSATA_testing(MSATA_CFG *msata_cfg, MSATA_RESULT *msata_result);
	int			TOB_MPCIE_testing(MPCIE_CFG *mpcie_cfg, MPCIE_RESULT *mpcie_result);
	int			TOB_RS232_testing(RS232_CFG *rs232_cfg, RS232_RESULT *rs232_result);
	int 		TOB_I2C_Testing(I2C_CFG *i2c_cfg, I2C_RESULT *i2c_result);
	int			TOB_SPI_testing(SPI_CFG *spi_cfg, SPI_RESULT *spi_result);
	int			TOB_UART_Testing(UART_CFG *uart_cfg, UART_RESULT *uart_result);
	int			TOB_FAN_Testing(FAN_CFG *fan_cfg, FAN_RESULT *fan_result);
	int			TOB_CANBus_Testing(CAN_CFG *can_cfg, CAN_RESULT *can_result);
	int			TOB_Sensors_Testing(SENSORS_CFG *sensors_cfg, SENSORS_RESULT *sensors_result);
	int 		TOB_USB_Testing(USB_CFG *usb_cfg, USB_RESULT *usb_result);
	int			TOB_M2_EKEY_Testing(M2_EKEY_CFG *ekey_cfg, M2_EKEY_RESULT *ekey_result);
	int			TOB_M2_MKEY_Testing( M2_MKEY_RESULT *mkey_result);
	int 		TOB_WriteEEPROM(EEPROM_CFG *eeprom_cfg, EEPROM_Result *eeprom_result);
	int			TOB_ReadEEPROM(EEPROM_CFG *eeprom_cfg, EEPROM_Result *eeprom_result);
}
#else
extern void 	TOB_GetLibVersion(char *szVersion);
extern void		TOB_SetLogFunc(CALLBACK_LOG_FUNC func);
extern void		TOB_GetDeviceInfo(DEVINFO_RESULT *devinfo_result);
extern int		TOB_LAN_testing(LAN_CFG *lan_cfg, LAN_RESULT *lan_result);
extern int		TOB_WIFI_testing(WIFI_RESULT *wifi_result);
extern int		TOB_BT_testing(BT_RESULT *bt_result);
extern int		TOB_SDCARD_testing(SDCARD_CFG *sdcard_cfg, SDCARD_RESULT *sdcard_result);
extern int		TOB_MSATA_testing(MSATA_CFG *msata_cfg, MSATA_RESULT *msata_result);
extern int		TOB_MPCIE_testing(MPCIE_CFG *mpcie_cfg, MPCIE_RESULT *mpcie_result);
extern int		TOB_RS232_testing(RS232_CFG *rs232_cfg, RS232_RESULT *rs232_result);
extern int		TOB_I2C_Testing(I2C_CFG *i2c_cfg, I2C_RESULT *i2c_result);
extern int		TOB_SPI_testing(SPI_CFG *spi_cfg, SPI_RESULT *spi_result);
extern int		TOB_UART_Testing(UART_CFG *uart_cfg, UART_RESULT *uart_result);
extern int		TOB_FAN_Testing(FAN_CFG *fan_cfg, FAN_RESULT *fan_result);
extern int		TOB_CANBus_Testing(CAN_CFG *can_cfg, CAN_RESULT *can_result);
extern int		TOB_Sensors_Testing(SENSORS_CFG *sensors_cfg, SENSORS_RESULT *sensors_result);
extern int		TOB_USB_Testing(USB_CFG *usb_cfg, USB_RESULT *usb_result);
extern int		TOB_M2_EKEY_Testing(M2_EKEY_CFG *ekey_cfg, M2_EKEY_RESULT *ekey_result);
extern int		TOB_M2_MKEY_Testing( M2_MKEY_RESULT *mkey_result);
extern int 		TOB_WriteEEPROM(EEPROM_CFG *eeprom_cfg, EEPROM_Result *eeprom_result);
extern int		TOB_ReadEEPROM(EEPROM_CFG *eeprom_cfg, EEPROM_Result *eeprom_result);
#endif
#endif
