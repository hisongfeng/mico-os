#include "debug.h"
#include "common.h"
#include "moc_api.h"
#include "moc_api_sep.h"

static kernel_api_t _kernel_api;

static mico_system_config_t* _system_config_get( void )
{
  static mico_system_config_t cfg;
 // _kernel_api.os_apis->system_config(0, &cfg);
  printf("config get\r\n");
  return &cfg;
}

static void _system_config_set( mico_system_config_t *cfg )
{
  //_kernel_api.os_apis->system_config(1, cfg);
  printf("config set");
}

#ifndef MICO_DISABLE_STDIO

#ifndef STDIO_BUFFER_SIZE
#define STDIO_BUFFER_SIZE   64
#endif

static const platform_uart_config_t stdio_uart_config =
{
    .baud_rate = STDIO_UART_BAUDRATE,
    .data_width = DATA_WIDTH_8BIT,
    .parity = NO_PARITY,
    .stop_bits = STOP_BITS_1,
    .flow_control = FLOW_CONTROL_DISABLED,
    .flags = 0,
};

static volatile ring_buffer_t stdio_rx_buffer;
static volatile uint8_t stdio_rx_data[STDIO_BUFFER_SIZE];

void init_debug_uart(void)
{
	ring_buffer_init( (ring_buffer_t*) &stdio_rx_buffer, (uint8_t*) stdio_rx_data, STDIO_BUFFER_SIZE );
	MicoUartInitialize(STDIO_UART, &stdio_uart_config,
                        (ring_buffer_t*) &stdio_rx_buffer );
}
#else
void init_debug_uart(void)
{
    return;
}
#endif

static void _mico_rtos_thread_yield(void)
{
   mico_rtos_delay_milliseconds( 0 );
}


mico_api_t *moc_adapter(new_mico_api_t *new_mico_api)
{
  static mico_api_t mico_api;
  new_mico_api->mico_api_get(API_VERSION_V1, &_kernel_api);
  
  /* automatically generated by python script */
  mico_api.library_version = new_mico_api->library_version;
  
  mico_api.system_config_get = _system_config_get;
  mico_api.system_config_set = _system_config_set;
  mico_api.mxchipInit = (void(*)())_kernel_api.os_apis->mxchipInit;

  mico_api.mico_rtos_create_thread = (int (*)(void **, uint8_t, char const *, void (*)(uint32_t), uint32_t, void *))_kernel_api.os_apis->mico_rtos_create_thread;
  mico_api.mico_rtos_delete_thread = _kernel_api.os_apis->mico_rtos_delete_thread;
  mico_api.mico_rtos_delete_thread = _kernel_api.os_apis->mico_rtos_delete_thread;
  mico_api.mico_rtos_thread_yield = _mico_rtos_thread_yield;
  mico_api.mico_rtos_suspend_thread = _kernel_api.os_apis->mico_rtos_suspend_thread;
  mico_api.mico_rtos_suspend_all_thread = _kernel_api.os_apis->mico_rtos_suspend_all_thread;
  mico_api.mico_rtos_resume_all_thread = (long(*)(void))_kernel_api.os_apis->mico_rtos_resume_all_thread;
  mico_api.mico_rtos_thread_join = _kernel_api.os_apis->mico_rtos_thread_join;
  mico_api.mico_rtos_thread_force_awake = _kernel_api.os_apis->mico_rtos_thread_force_awake;
  mico_api.mico_rtos_is_current_thread = _kernel_api.os_apis->mico_rtos_is_current_thread;
  mico_api.mico_thread_sleep = _kernel_api.os_apis->mico_thread_sleep;
  mico_api.mico_thread_msleep = _kernel_api.os_apis->mico_thread_msleep;
  mico_api.mico_rtos_init_semaphore = _kernel_api.os_apis->mico_rtos_init_semaphore;
  mico_api.mico_rtos_set_semaphore = _kernel_api.os_apis->mico_rtos_set_semaphore;
  mico_api.mico_rtos_get_semaphore = _kernel_api.os_apis->mico_rtos_get_semaphore;
  mico_api.mico_rtos_deinit_semaphore = _kernel_api.os_apis->mico_rtos_deinit_semaphore;
  mico_api.mico_rtos_init_mutex = _kernel_api.os_apis->mico_rtos_init_mutex;
  mico_api.mico_rtos_lock_mutex = _kernel_api.os_apis->mico_rtos_lock_mutex;
  mico_api.mico_rtos_unlock_mutex = _kernel_api.os_apis->mico_rtos_unlock_mutex;
  mico_api.mico_rtos_deinit_mutex = _kernel_api.os_apis->mico_rtos_deinit_mutex;
  mico_api.mico_rtos_init_queue = _kernel_api.os_apis->mico_rtos_init_queue;
  mico_api.mico_rtos_push_to_queue = _kernel_api.os_apis->mico_rtos_push_to_queue;
  mico_api.mico_rtos_pop_from_queue = _kernel_api.os_apis->mico_rtos_pop_from_queue;
  mico_api.mico_rtos_deinit_queue = _kernel_api.os_apis->mico_rtos_deinit_queue;
  mico_api.mico_rtos_is_queue_empty = _kernel_api.os_apis->mico_rtos_is_queue_empty;
  mico_api.mico_rtos_is_queue_full = (int (*)(void * *))_kernel_api.os_apis->mico_rtos_is_queue_full;
  mico_api.mico_get_time = _kernel_api.os_apis->mico_get_time;
  mico_api.mico_init_timer = _kernel_api.os_apis->mico_init_timer;
  mico_api.mico_start_timer = _kernel_api.os_apis->mico_start_timer;
  mico_api.mico_stop_timer = _kernel_api.os_apis->mico_stop_timer;
  mico_api.mico_reload_timer = _kernel_api.os_apis->mico_reload_timer;
  mico_api.mico_deinit_timer = _kernel_api.os_apis->mico_deinit_timer;
  mico_api.mico_is_timer_running = _kernel_api.os_apis->mico_is_timer_running;
  mico_api.mico_create_event_fd = _kernel_api.os_apis->mico_create_event_fd;
  mico_api.mico_delete_event_fd = _kernel_api.os_apis->mico_delete_event_fd;
  mico_api.SetTimer = NULL;
  mico_api.SetTimer_uniq = NULL;
  mico_api.UnSetTimer = NULL;
  mico_api.mico_memory_info = (micoMemInfo_t* (*)( void ))_kernel_api.os_apis->mico_memory_info;
  mico_api.malloc = _kernel_api.os_apis->malloc;
  mico_api.realloc = _kernel_api.os_apis->realloc;
  mico_api.free = _kernel_api.os_apis->free;
  mico_api.calloc = (void *(*)(int, int))_kernel_api.os_apis->calloc;
  mico_api.heap_insert = _kernel_api.os_apis->heap_insert;
  
  mico_api.socket = NULL;
  mico_api.setsockopt = NULL;
  mico_api.getsockopt = NULL;
  mico_api.bind = NULL;
  mico_api.connect = NULL;
  mico_api.listen = NULL;
  mico_api.accept = NULL;
  mico_api.select = NULL;
  mico_api.send = NULL;
  mico_api.write = NULL;
  mico_api.sendto = NULL;
  mico_api.recv = NULL;
  mico_api.read = NULL;
  mico_api.recvfrom = NULL;
  mico_api.close = NULL;
  mico_api.inet_addr = NULL;
  mico_api.inet_ntoa = NULL;
  mico_api.gethostbyname = NULL;
  mico_api.set_tcp_keepalive = NULL;
  mico_api.get_tcp_keepalive = NULL;
  
  mico_api.lwip_apis = _kernel_api.lwip_apis;
  
  mico_api.ssl_set_cert = _kernel_api.ssl_crypto_apis->ssl_set_cert;
  mico_api.ssl_connect = _kernel_api.ssl_crypto_apis->ssl_connect;
  mico_api.ssl_accept = _kernel_api.ssl_crypto_apis->ssl_accept;
  mico_api.ssl_send = _kernel_api.ssl_crypto_apis->ssl_send;
  mico_api.ssl_recv = _kernel_api.ssl_crypto_apis->ssl_recv;
  mico_api.ssl_close = _kernel_api.ssl_crypto_apis->ssl_close;
  mico_api.set_ssl_client_version = _kernel_api.ssl_crypto_apis->set_ssl_client_version;
  mico_api.ssl_nonblock_connect = _kernel_api.ssl_crypto_apis->ssl_nonblock_connect;
  mico_api.ssl_set_using_nonblock = _kernel_api.ssl_crypto_apis->ssl_set_using_nonblock;
  mico_api.ssl_pending = _kernel_api.ssl_crypto_apis->ssl_pending;
  mico_api.ssl_get_error = _kernel_api.ssl_crypto_apis->ssl_get_error;
  mico_api.ssl_set_client_cert = _kernel_api.ssl_crypto_apis->ssl_set_client_cert;
  mico_api.ssl_connect_sni = _kernel_api.ssl_crypto_apis->ssl_connect_sni;
  
  mico_api.InitMd5 = (void (*)(md5_context*))_kernel_api.ssl_crypto_apis->InitMd5;
  mico_api.Md5Update = (void (*)(md5_context*,unsigned char*, int))_kernel_api.ssl_crypto_apis->Md5Update;
  mico_api.Md5Final = (void (*)(md5_context*,uint8_t*))_kernel_api.ssl_crypto_apis->Md5Final;
  mico_api.Md5Hash = _kernel_api.ssl_crypto_apis->Md5Hash;
  mico_api.AesEncryptDirect = _kernel_api.ssl_crypto_apis->AesEncryptDirect;
  mico_api.AesDecryptDirect = _kernel_api.ssl_crypto_apis->AesDecryptDirect;
  mico_api.AesSetKeyDirect = _kernel_api.ssl_crypto_apis->AesSetKeyDirect;
  mico_api.aes_encrypt = _kernel_api.ssl_crypto_apis->aes_encrypt;
  mico_api.aes_decrypt = _kernel_api.ssl_crypto_apis->aes_decrypt;
  mico_api.AesSetKey = _kernel_api.ssl_crypto_apis->AesSetKey;
  mico_api.AesSetIV = _kernel_api.ssl_crypto_apis->AesSetIV;
  mico_api.AesCbcEncrypt = _kernel_api.ssl_crypto_apis->AesCbcEncrypt;
  mico_api.AesCbcDecrypt = _kernel_api.ssl_crypto_apis->AesCbcDecrypt;

  mico_api.wlan_get_mac_address = _kernel_api.wifi_apis->wlan_get_mac_address;
  mico_api.wlan_get_mac_address_by_interface = _kernel_api.wifi_apis->wlan_get_mac_address_by_interface;
  mico_api.mico_wlan_get_channel = _kernel_api.wifi_apis->mico_wlan_get_channel;
  mico_api.wlan_driver_version = _kernel_api.wifi_apis->wlan_driver_version;
  mico_api.micoWlanStart = _kernel_api.wifi_apis->micoWlanStart;
  mico_api.micoWlanStartAdv = _kernel_api.wifi_apis->micoWlanStartAdv;
  mico_api.micoWlanGetIPStatus = _kernel_api.wifi_apis->micoWlanGetIPStatus;
  mico_api.micoWlanGetLinkStatus = _kernel_api.wifi_apis->micoWlanGetLinkStatus;
  mico_api.micoWlanStartScan = (int(*)(void))_kernel_api.wifi_apis->micoWlanStartScan;
  mico_api.micoWlanStartScanAdv = (int(*)(void))_kernel_api.wifi_apis->micoWlanStartScanAdv;
  mico_api.micoWlanPowerOff = _kernel_api.wifi_apis->micoWlanPowerOff;
  mico_api.micoWlanPowerOn = _kernel_api.wifi_apis->micoWlanPowerOn;
  mico_api.micoWlanSuspend = _kernel_api.wifi_apis->micoWlanSuspend;
  mico_api.micoWlanSuspendStation = _kernel_api.wifi_apis->micoWlanSuspendStation;
  mico_api.micoWlanSuspendSoftAP = _kernel_api.wifi_apis->micoWlanSuspendSoftAP;
  mico_api.micoWlanStartEasyLink = _kernel_api.wifi_apis->micoWlanStartEasyLink;
  mico_api.micoWlanStartEasyLinkPlus = _kernel_api.wifi_apis->micoWlanStartEasyLink;
  mico_api.micoWlanStopEasyLink = _kernel_api.wifi_apis->micoWlanStopEasyLink;
  mico_api.micoWlanStopEasyLinkPlus = _kernel_api.wifi_apis->micoWlanStopEasyLink;
  mico_api.micoWlanStartWPS = NULL;
  mico_api.micoWlanStopWPS = NULL;
  mico_api.micoWlanStartAirkiss = _kernel_api.wifi_apis->micoWlanStartEasyLink;
  mico_api.micoWlanStopAirkiss = _kernel_api.wifi_apis->micoWlanStopEasyLink;
  mico_api.micoWlanEnablePowerSave = _kernel_api.wifi_apis->micoWlanEnablePowerSave;
  mico_api.micoWlanDisablePowerSave = _kernel_api.wifi_apis->micoWlanDisablePowerSave;
  mico_api.wifimgr_debug_enable = _kernel_api.wifi_apis->wifimgr_debug_enable;
  mico_api.mico_wlan_monitor_rx_type = _kernel_api.wifi_apis->mico_wlan_monitor_rx_type;
  mico_api.mico_wlan_start_monitor = _kernel_api.wifi_apis->mico_wlan_start_monitor;
  mico_api.mico_wlan_stop_monitor = _kernel_api.wifi_apis->mico_wlan_stop_monitor;
  mico_api.mico_wlan_monitor_set_channel = _kernel_api.wifi_apis->mico_wlan_monitor_set_channel;
  mico_api.mico_wlan_register_monitor_cb = _kernel_api.wifi_apis->mico_wlan_register_monitor_cb;
  mico_api.wlan_set_channel = _kernel_api.wifi_apis->wlan_set_channel;
  mico_api.mxchip_active_scan = _kernel_api.wifi_apis->mxchip_active_scan;
  mico_api.wifi_manage_custom_ie_add = _kernel_api.wifi_apis->wifi_manage_custom_ie_add;
  mico_api.wifi_manage_custom_ie_delete = _kernel_api.wifi_apis->wifi_manage_custom_ie_delete;
  
  mico_api.cli_init = _kernel_api.cli_apis->cli_init;
  mico_api.cli_register_command = _kernel_api.cli_apis->cli_register_command;
  mico_api.cli_unregister_command = _kernel_api.cli_apis->cli_unregister_command;
  mico_api.wifistate_Command = _kernel_api.cli_apis->wifistate_Command;
  mico_api.wifidebug_Command = _kernel_api.cli_apis->wifidebug_Command;
  mico_api.wifiscan_Command = _kernel_api.cli_apis->wifiscan_Command;
  mico_api.ifconfig_Command = _kernel_api.cli_apis->ifconfig_Command;
  mico_api.arp_Command = _kernel_api.cli_apis->arp_Command;
  mico_api.ping_Command = _kernel_api.cli_apis->ping_Command;
  mico_api.dns_Command = _kernel_api.cli_apis->dns_Command;
  mico_api.task_Command = _kernel_api.cli_apis->task_Command;
  mico_api.socket_show_Command = _kernel_api.cli_apis->socket_show_Command;
  mico_api.memory_show_Command = _kernel_api.cli_apis->memory_show_Command;
  mico_api.memory_dump_Command = _kernel_api.cli_apis->memory_dump_Command;
  mico_api.memory_set_Command = _kernel_api.cli_apis->memory_set_Command;
  mico_api.memp_dump_Command = _kernel_api.cli_apis->memp_dump_Command;
  mico_api.driver_state_Command = _kernel_api.cli_apis->driver_state_Command;
  mico_api.iperf_Command = _kernel_api.cli_apis->iperf_Command;
  
  mico_api.MicoFlashGetInfo = _kernel_api.flash_apis->MicoFlashGetInfo;
  mico_api.MicoFlashErase = _kernel_api.flash_apis->MicoFlashErase;
  mico_api.MicoFlashWrite = _kernel_api.flash_apis->MicoFlashWrite;
  mico_api.MicoFlashRead = _kernel_api.flash_apis->MicoFlashRead;
  mico_api.MicoFlashEnableSecurity = _kernel_api.flash_apis->MicoFlashEnableSecurity;
  mico_api.MicoGpioInitialize = _kernel_api.gpio_apis->MicoGpioInitialize;
  mico_api.MicoGpioFinalize = _kernel_api.gpio_apis->MicoGpioFinalize;
  mico_api.MicoGpioOutputHigh = _kernel_api.gpio_apis->MicoGpioOutputHigh;
  mico_api.MicoGpioOutputLow = _kernel_api.gpio_apis->MicoGpioOutputLow;
  mico_api.MicoGpioOutputTrigger = _kernel_api.gpio_apis->MicoGpioOutputTrigger;
  mico_api.MicoGpioInputGet = _kernel_api.gpio_apis->MicoGpioInputGet;
  mico_api.MicoGpioEnableIRQ = _kernel_api.gpio_apis->MicoGpioEnableIRQ;
  mico_api.MicoGpioDisableIRQ = _kernel_api.gpio_apis->MicoGpioDisableIRQ;
  mico_api.MicoUartInitialize = _kernel_api.uart_apis->MicoUartInitialize;
  mico_api.MicoUartFinalize = _kernel_api.uart_apis->MicoUartFinalize;
  mico_api.MicoUartSend = _kernel_api.uart_apis->MicoUartSend;
  mico_api.MicoUartRecv = _kernel_api.uart_apis->MicoUartRecv;
  mico_api.MicoUartGetLengthInBuffer = _kernel_api.uart_apis->MicoUartGetLengthInBuffer;
  mico_api.MicoUartPinRedirect = _kernel_api.uart_apis->MicoUartPinRedirect;
  
  mico_api.pm_mcu_state = _kernel_api.ps_apis->pm_mcu_state;
  mico_api.pm_wakeup_source = _kernel_api.ps_apis->pm_wakeup_source;
  mico_api.wifi_off_mcu_standby = (void(*)(int))(_kernel_api.ps_apis->wifi_off_mcu_standby);
  mico_api.MicoMcuPowerSaveConfig = _kernel_api.ps_apis->MicoMcuPowerSaveConfig;
  mico_api.debug_putchar = _kernel_api.os_apis->debug_putchar;
  mico_api.MicoSystemReboot = _kernel_api.os_apis->MicoSystemReboot;
  mico_api.get_ali_key = NULL;
  mico_api.get_ali_secret = NULL;
  mico_api.MicoRtcInitialize = _kernel_api.rtc_apis->MicoRtcInitialize;
  mico_api.MicoRtcGetTime = _kernel_api.rtc_apis->MicoRtcGetTime;
  mico_api.MicoRtcSetTime = _kernel_api.rtc_apis->MicoRtcSetTime;
  mico_api.localtime = _kernel_api.os_apis->localtime;
  mico_api.asctime = _kernel_api.os_apis->asctime;
  mico_api.wifi_set_country = _kernel_api.wifi_apis->wifi_set_country;
  mico_api.switch_active_firmrware = NULL;
  mico_api.last_reset_reason = _kernel_api.os_apis->last_reset_reason;
  mico_api.aon_write = _kernel_api.os_apis->aon_write;
  mico_api.aon_read = _kernel_api.os_apis->aon_read;
  mico_api.ssl_get_fd = _kernel_api.ssl_crypto_apis->ssl_get_fd;
  mico_api.get_random_sequence = _kernel_api.os_apis->get_random_sequence;
  mico_api.ssl_set_loggingcb = _kernel_api.ssl_crypto_apis->ssl_loggingcb;
  mico_api.wlan_inject_frame = _kernel_api.wifi_apis->wlan_inject_frame;
  mico_api.wlan_rx_mgmt_indication = NULL;
  mico_api.wlan_remain_on_channel = NULL;
  mico_api.wifi_bridge_mode_enable = NULL;
  mico_api.wifi_bridge_mode_disable = NULL;
  mico_api.send_easylink_minus = _kernel_api.wifi_apis->send_easylink_minus;
  mico_api.ssl_socket = (int(*)(void*))(_kernel_api.ssl_crypto_apis->ssl_get_fd);

  mico_api.i2c_apis = _kernel_api.i2c_apis;
  mico_api.spi_apis = _kernel_api.spi_apis;
  mico_api.pwm_apis = _kernel_api.pwm_apis;
  mico_api.wdg_apis = _kernel_api.wdg_apis;
  mico_api.adc_apis = _kernel_api.adc_apis;
  mico_api.gtimer_apis = _kernel_api.gtimer_apis;

  return &mico_api;
}

int debug_putchar(char *ch, int len)
{
	return _kernel_api.os_apis->debug_putchar(ch, len);
}

int debug_gettchar(char *ch)
{
	return _kernel_api.os_apis->debug_getchar(ch);
}

int mico_wlan_monitor_no_easylink(void)
{
	return _kernel_api.wifi_apis->mico_wlan_monitor_no_easylink();
}

int mico_wlan_monitor_rx_mimo(int enable)
{
    return _kernel_api.wifi_apis->mico_wlan_monitor_rx_mimo(enable);
}

int mico_wlan_monitor_with_easylink(void)
{
	return _kernel_api.wifi_apis->mico_wlan_monitor_with_easylink();
}

int wlan_rx_mgnt_set(int enable, mgnt_handler_t cb)
{
	return _kernel_api.wifi_apis->wlan_rx_mgnt_set(enable, cb);
}

OSStatus mico_wlan_register_recv_mgnt(monitor_cb_t fn)
{
    if (fn == NULL)
        return _kernel_api.wifi_apis->wlan_rx_mgnt_set(false, NULL);
    else
        return _kernel_api.wifi_apis->wlan_rx_mgnt_set(true, fn);
}

void autoconfig_start(int seconds, int mode)
{
	_kernel_api.wifi_apis->autoconfig_start(seconds, mode);
}

void wlan_set_softap_tdma(int value)
{
	_kernel_api.wifi_apis->wlan_set_softap_tdma(value);
}

int wifi_off_fastly(void)
{
    return _kernel_api.wifi_apis->wifi_off_fastly();
}

int mico_wlan_easylink_uap_start(int timeout, char *ssid, char*key, int channel)
{
    return _kernel_api.wifi_apis->OpenEasylink_softap(timeout, ssid, key, channel);
}

void mico_wlan_start_ap_with_asso_cb(char *ssid, char *key, int channel, asso_event_handler_t fn)
{
    _kernel_api.wifi_apis->mico_wlan_start_ap_with_asso_cb(ssid, key, channel, fn);
}

int mico_wlan_start_monitor_awss()
{
	return _kernel_api.wifi_apis->mico_wlan_start_monitor_awss();
}

int mico_wlan_stop_monitor_awss()
{
	return _kernel_api.wifi_apis->mico_wlan_stop_monitor_awss();
}

void ssl_set_ecc(int enable)
{
    _kernel_api.ssl_crypto_apis->ssl_set_ecc(enable);
}

/* return 1=success; 0=fail*/
int disable_log_uart(void)
{
    return _kernel_api.uart_apis->disable_log_uart();
}

void mico_rtos_resume_thread(mico_thread_t* thread)
{
    _kernel_api.os_apis->mico_rtos_resume_thread(thread);
}

#define extra_apis _kernel_api.ssl_crypto_apis->extra_crypto_apis

#define EXTRA_CRYPTO_CHECK() if (EXTRA_CRYPTO_FLAG != _kernel_api.ssl_crypto_apis->extra_crypto_flag) return -1;
        
int  InitRng(CyaSSL_RNG* rng)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->InitRng(rng);
}
int  RNG_GenerateBlock(CyaSSL_RNG* rng, byte* b, word32 sz)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->RNG_GenerateBlock(rng, b, sz);
}
int  RNG_GenerateByte(CyaSSL_RNG* rng, byte* b)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->RNG_GenerateByte(rng, b);
}
int FreeRng(CyaSSL_RNG* rng)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->FreeRng(rng);
}


int  RsaPublicKeyDecode(const byte* input, word32* inOutIdx, RsaKey* key, word32 inSz)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->RsaPublicKeyDecode(input, inOutIdx, key, inSz);
}
int  InitRsaKey(RsaKey* key, void* ptr)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->InitRsaKey(key, ptr);
}
int  FreeRsaKey(RsaKey* key)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->FreeRsaKey(key);
}
int  RsaPublicEncrypt(const byte* in, word32 inLen, byte* out,
                         word32 outLen, RsaKey* key, CyaSSL_RNG* rng)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->RsaPublicEncrypt(in, inLen, out,
                         outLen, key, rng);
}
int  RsaSSL_Verify(const byte* in, word32 inLen, byte* out,
                      word32 outLen, RsaKey* key)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->RsaSSL_Verify(in, inLen, out, outLen, key);
}
int  RsaEncryptSize(RsaKey* key)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->RsaEncryptSize(key);
}

int InitSha256(Sha256* sha)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->InitSha256(sha);
}
int Sha256Update(Sha256* sha, const byte* data, word32 len)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->Sha256Update(sha, data, len);
}
int Sha256Final(Sha256* sha, byte* out)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->Sha256Final(sha, out);
}

int InitSha(Sha* sha)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->InitSha(sha);
}
int ShaUpdate(Sha* sha, const byte* data, word32 len)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->ShaUpdate(sha, data, len);
}
int ShaFinal(Sha* sha, byte* out)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->ShaFinal(sha, out);
}

int HmacSetKey(Hmac* hmac, int type, const byte* key, word32 keySz)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->HmacSetKey(hmac, type, key, keySz);
}
int HmacUpdate(Hmac* hmac, const byte* in, word32 sz)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->HmacUpdate(hmac, in, sz);
}
int HmacFinal(Hmac* hmac, byte* out)
{
    EXTRA_CRYPTO_CHECK();
    return extra_apis->HmacFinal(hmac, out);
}

void* ssl_connect_dtls(int fd, int calen, char*ca, int *errno)
{
    return _kernel_api.ssl_crypto_apis->ssl_connect_dtls(fd, calen, ca, errno);
}

void ssl_set_alpn_list(char*list)
{
    _kernel_api.ssl_crypto_apis->ssl_set_alpn_list(list);
}

int hardfault_get(char *msg, int len)
{
    return _kernel_api.os_apis->hardfault_get(msg, len);
}

int mico_change_timer_period( mico_timer_t* timer, uint32_t new_period )
{
    return _kernel_api.os_apis->mico_change_timer_period(timer, new_period );
}

int mico_init_once_timer( mico_timer_t* timer, uint32_t time_ms, timer_handler_t function, void* arg )
{
    return _kernel_api.os_apis->mico_init_once_timer( timer, time_ms, function, arg );
}

OSStatus MicoRtcSetalarm(mico_rtc_time_t *time, rtc_irq_handler handler)
{
    return _kernel_api.rtc_apis->MicoRtcSetalarm( time, handler );
}

/* Insert an AP info */
OSStatus micoWlanAddExtraNetowrk(char *ssid, char *key, uint8_t key_len)
{
    return _kernel_api.wifi_apis->wlan_add_extra_network(ssid, key, key_len);
}

char *mico_current_task_name(void)
{
    return _kernel_api.os_apis->get_current_task_name();
}

int mico_rtos_get_task_status(mico_thread_t* thread)
{
	return _kernel_api.os_apis->mico_rtos_get_task_status(thread);
}

OSStatus MicoRtcGetSeconds(uint32_t* time)
{
	return _kernel_api.rtc_apis->MicoRtcGetSeconds(time); 
}

OSStatus MicoRtcSetSeconds(uint32_t* time)
{
	return _kernel_api.rtc_apis->MicoRtcSetSeconds(time); 
}

OSStatus mico_rtos_eventgroup_init(void *handler)
{
    return _kernel_api.os_apis->mico_rtos_eventgroup_init(handler);
}

OSStatus mico_rtos_eventgroup_deinit(void * handler)
{
    return _kernel_api.os_apis->mico_rtos_eventgroup_deinit(handler);
}

int mico_rtos_eventgroup_set_bits(void * handler, int bits)
{
    return _kernel_api.os_apis->mico_rtos_eventgroup_set_bits(handler, bits);
}

int mico_rtos_eventgroup_clear_bits(void * handler, int bits)
{
    return _kernel_api.os_apis->mico_rtos_eventgroup_clear_bits(handler, bits);
}

int mico_rtos_eventgroup_wait_bits(void * handler, int bits, int isClearOnExit, int isWaitForAllBits, int waitMs)
{
    return _kernel_api.os_apis->mico_rtos_eventgroup_wait_bits(handler, bits, isClearOnExit, isWaitForAllBits, waitMs);
}

OSStatus MicoPwmSwitchPin( mico_pwm_t pwm, mico_gpio_t gpio )
{
    return _kernel_api.pwm_apis->pwm_switch_pin(pwm, gpio);
}

mico_thread_t mico_rtos_get_current_thread( void )
{
    return _kernel_api.os_apis->mico_rtos_get_current_thread();
}

void mico_rtos_set_thread_arg(mico_thread_t *thread, void *arg)
{
    _kernel_api.os_apis->mico_rtos_set_thread_arg(thread, arg);
}

void *mico_rtos_get_thread_arg(mico_thread_t *thread)
{
    return _kernel_api.os_apis->mico_rtos_get_thread_arg(thread);
}

mico_thread_t* mico_rtos_create_thread_static(uint8_t priority, const char* name, mico_thread_function_t function, uint32_t stack_size, void* arg, uint8_t *stackbuf, uint8_t *threadbuf )
{
    return _kernel_api.os_apis->mico_rtos_create_thread_static(priority, name, function, stack_size, arg, stackbuf, threadbuf);
}

OSStatus mico_rtos_try_lock_mutex( mico_mutex_t* mutex )
{
    return _kernel_api.os_apis->mico_rtos_try_lock_mutex(mutex);
}