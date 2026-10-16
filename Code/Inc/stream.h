#ifndef __STREAM_H__
#define __STREAM_H__

#include "sys.h"

#include <cstdint>
#if ENABLE_OS_SUPPORT
#include "FreeRTOS.h"
#include "semphr.h"
#endif

#define DEFAULT_STREAM_BUFF_SIZE 128
#define DEFAULT_STREAM_PAYLOAD_SIZE 128

/**
 * @brief 流输出回调函数
 * @note  无操作系统下将以阻塞的形式将流输出 阻塞时间 @ref DEFAULT_STREAM_OUTPUT_TIMEOUT_TIME
 * @param pCallback
 * @param handle -用户自定义参数句柄
 */
typedef void (*stream_out_callback_t)(uint8_t *data, uint16_t size, void *handle);
/**
 * @brief 流运行回调函数
 * @param handle -用户自定义参数句柄
 * @note  -用于处理接收数据流的功能函数
 *        -无操作系统下以轮询方式调用
 *        -有操作系统下将进入阻塞状态
 */
typedef void (*stream_run_callback_t)(void *handle);
/**
 * @brief 基于数据流处理的类
 * @note    -注册数据流输出回调函数 StreamOutCallback 对象可以是 UART DMA SPI 等
 *          -提供数据接收缓冲区 payload_ 在创建时默认分配 @ref DEFAULT_STREAM_PAYLOAD_SIZE 大小的内存
 *          -提供数据输出缓冲区 buffer_ 在创建时默认分配 @ref DEFAULT_STREAM_BUFF_SIZE 大小的内存
 */
class StreamProcessor
{
  public:
    uint8_t *payload_;
    uint16_t size_;
    // clang-format off
	StreamProcessor(void *handle) : StreamProcessor(DEFAULT_STREAM_PAYLOAD_SIZE, handle) {}
    // clang-format on
    StreamProcessor(uint16_t size, void *handle);
    StreamProcessor(const StreamProcessor &obj);
    ~StreamProcessor();

    StreamProcessor &operator=(const StreamProcessor &obj);

    void RegisterStreamOutCallback(stream_out_callback_t callback);
    void RegisterStreamRunCallback(stream_run_callback_t callback);
    void SetHandle(void *handle);
    void GetHandle();
    void Run();
    void Print(const char *fmt, ...);
    void Print(uint8_t *data, uint16_t size);

#if ENABLE_OS_SUPPORT
    void SendComplete(BaseType_t task_woken = pdFALSE);
    void ReceiveComplete(uint16_t size, BaseType_t task_woken = pdFALSE);
#else
    void SendComplete();
    void ReceiveComplete(uint16_t size);
#endif

  private:
    char buffer_[DEFAULT_STREAM_BUFF_SIZE];
    void *handle_;
    uint16_t payload_size_;
    stream_out_callback_t OutCallback;
    stream_run_callback_t RunCallback;

#if ENABLE_OS_SUPPORT
    SemaphoreHandle_t rx_semaphore_;
    SemaphoreHandle_t tx_semaphore_;
#else
    volatile bool tx_complete_;
    volatile bool rx_complete_;
#endif
};

#endif