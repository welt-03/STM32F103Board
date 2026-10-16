#include "stream.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>

StreamProcessor::StreamProcessor(uint16_t size, void *handle)
{
    payload_size_ = size;
    payload_ = new uint8_t[payload_size_];

    handle_ = handle;
    OutCallback = nullptr;
    RunCallback = nullptr;

#if ENABLE_OS_SUPPORT
    tx_semaphore_ = xSemaphoreCreateBinary();
    rx_semaphore_ = xSemaphoreCreateBinary();
    xSemaphoreGive(tx_semaphore_);
#else
    tx_complete_ = true;
    rx_complete_ = false;
#endif
}
StreamProcessor::StreamProcessor(const StreamProcessor &obj)
{
    payload_size_ = obj.payload_size_;
    payload_ = new uint8_t[payload_size_];

    size_ = obj.size_;
    memcpy(payload_, obj.payload_, obj.size_);

    handle_ = obj.handle_;
    OutCallback = obj.OutCallback;
    RunCallback = obj.RunCallback;

#if ENABLE_OS_SUPPORT
    tx_semaphore_ = xSemaphoreCreateBinary();
    rx_semaphore_ = xSemaphoreCreateBinary();
    xSemaphoreGive(tx_semaphore_);
#else
    tx_complete_ = true;
    rx_complete_ = false;
#endif
}

StreamProcessor::~StreamProcessor()
{
    delete[] payload_;
    payload_ = nullptr;
    handle_ = nullptr;
    OutCallback = nullptr;
    RunCallback = nullptr;
}

StreamProcessor &StreamProcessor::operator=(const StreamProcessor &obj)
{
    if (this != &obj)
    {
        if (payload_ != nullptr)
        {
            delete[] payload_;
            payload_ = nullptr;
        }
        payload_size_ = obj.payload_size_;
        payload_ = new uint8_t[payload_size_];

        size_ = obj.size_;
        memcpy(payload_, obj.payload_, obj.size_);

        handle_ = obj.handle_;
        OutCallback = obj.OutCallback;
        RunCallback = obj.RunCallback;
    }
    return *this;
}

void StreamProcessor::RegisterStreamOutCallback(stream_out_callback_t pCallback)
{
    OutCallback = pCallback;
}

void StreamProcessor::RegisterStreamRunCallback(stream_run_callback_t pCallback)
{
    RunCallback = pCallback;
}

#if ENABLE_OS_SUPPORT
void StreamProcessor::SendComplete(BaseType_t task_woken)
{
    xSemaphoreGiveFromISR(tx_semaphore_, &task_woken);
    portYIELD_FROM_ISR(task_woken);
}
void StreamProcessor::ReceiveComplete(uint16_t size, BaseType_t task_woken)
{
    size_ = size;
    xSemaphoreGiveFromISR(rx_semaphore_, &task_woken);
    portYIELD_FROM_ISR(task_woken);
}
#else
void StreamProcessor::SendComplete()
{
    tx_complete_ = true;
}

void StreamProcessor::ReceiveComplete(uint16_t size)
{
    size_ = size;
    rx_complete_ = true;
}
#endif // ENABLE_OS_SUPPORT

void StreamProcessor::Print(const char *fmt, ...)
{
#if ENABLE_OS_SUPPORT
    xSemaphoreTake(tx_semaphore_, portMAX_DELAY);
#else
    while (!tx_complete_)
        continue;
    tx_complete_ = false;
#endif
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer_, fmt, args);
    va_end(args);
    if (OutCallback != nullptr)
    {
        OutCallback((uint8_t *)buffer_, strlen(buffer_), handle_);
    }
}

void StreamProcessor::Print(uint8_t *data, uint16_t size)
{
#if ENABLE_OS_SUPPORT
    xSemaphoreTake(tx_semaphore_, portMAX_DELAY);
#else
    while (!tx_complete_)
        continue;
    tx_complete_ = false;
#endif
    memcpy(buffer_, data, size);
    if (OutCallback != nullptr)
    {
        OutCallback((uint8_t *)buffer_, size, handle_);
    }
}

void StreamProcessor::Run()
{
#if ENABLE_OS_SUPPORT
    xSemaphoreTake(rx_semaphore_, portMAX_DELAY);
    if (RunCallback != nullptr)
    {
        RunCallback(handle_);
    }
#else
    if (rx_complete_ == true)
    {
        if (RunCallback != nullptr)
        {
            RunCallback(handle_);
        }
        rx_complete_ = false;
    }
#endif // ENABLE_OS_SUPPORT
}