#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum hal_can_bus_e
{
    HAL_CAN_BUS_CAN0 = 0,
    HAL_CAN_BUS_CAN1,
} hal_can_bus_t;

typedef enum hal_can_bitrate_e
{
    HAL_CAN_BIT_RATE_125_KBITS = 0,
    HAL_CAN_BIT_RATE_250_KBITS,
    HAL_CAN_BIT_RATE_500_KBITS,
    HAL_CAN_BIT_RATE_1000_KBITS,
} hal_can_bitrate_t;

typedef enum hal_can_mode_e
{
    HAL_CAN_MODE_INIT = 0,
    HAL_CAN_MODE_NORMAL,
    HAL_CAN_MODE_SLEEP,
    HAL_CAN_MODE_TEST,
    HAL_CAN_MODE_SILENT,
    HAL_CAN_MODE_LOOP_BACK,
    HAL_CAN_MODE_DEBUG,
}hal_can_mode_t;

typedef struct hal_can_message_s {
    uint32_t id;
    uint8_t extended_id;
    uint8_t rtr;
    uint8_t dlc;
    uint8_t data[8];
    uint32_t timestamp;
}hal_can_message_t;

typedef void (*hal_can_rx_callback_t)(hal_can_dev_t dev);
typedef void (*hal_can_tx_callback_t)(hal_can_dev_t dev);
typedef void (*hal_can_error_callback_t)(hal_can_dev_t dev);

typedef struct hal_can_config_s{
    hal_can_bitrate_t bitrate;
    hal_can_mode_t mode;
    hal_can_rx_mode_t rx_mode;
    hal_can_rx_callback_t rx_callback;
    hal_can_tx_callback_t tx_callback;
    hal_can_error_callback_t error_callback;
}hal_can_config_t;

/*Pedir para explicar*/
typedef struct hal_can_dev_s* hal_can_dev_t; 

typedef struct hal_can_driver_s
{
    void (*init)(void);
    void (*deinit)(void);

    hal_can_dev_t (*open)(hal_can_bus_t bus, hal_can_config_t* cfg);
    void (*close)(hal_can_dev_t dev);

    hal_can_status_t (*transmit)(hal_can_dev_t dev, const hal_can_message_t* msg, uint32_t timeout_ms);
    hal_can_status_t (*receive)(hal_can_dev_t dev, hal_can_message_t* msg, uint32_t timeout_ms);

    int (*set_mode)(hal_can_dev_t dev, hal_can_mode_t mode);
    int (*set_filter)(hal_can_dev_t dev, uint32_t id, uint32_t mask, uint8_t extended);
} hal_can_driver_t;


void hal_can_init(void);
void hal_can_deinit(void);

hal_can_dev_t hal_can_open(hal_can_bus_t bus, hal_can_config_t* cfg);
void hal_can_close(hal_can_dev_t dev);

hal_can_status_t hal_can_transmit(hal_can_dev_t dev, const hal_can_message_t* msg, uint32_t timeout_ms);
hal_can_status_t hal_can_receive(hal_can_dev_t dev, hal_can_message_t* msg, uint32_t timeout_ms);

int hal_can_set_mode(hal_can_dev_t dev, hal_can_mode_t mode);
int hal_can_set_filter(hal_can_dev_t dev, uint32_t id, uint32_t mask, uint8_t extended);

#ifdef __cplusplus
}
#endif
