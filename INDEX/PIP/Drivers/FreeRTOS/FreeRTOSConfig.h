#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
  #include <stdint.h>
  void xPortSysTickHandler(void);
#endif

/* ===================== 内核基础配置 ===================== */
#define configENABLE_FPU                         0
#define configENABLE_MPU                         0

#define configUSE_IDLE_HOOK                      0
#define configUSE_TICK_HOOK                      0
#define configUSE_DAEMON_TASK_STARTUP_HOOK       0
#define configUSE_PREEMPTION                     1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION  0
#define configUSE_TICKLESS_IDLE                  0
#define configUSE_TIME_SLICING                   1
#define configIDLE_SHOULD_YIELD                  1
#define configUSE_16_BIT_TICKS                   0

/* ===================== 时钟与节拍配置 ===================== */
#define configCPU_CLOCK_HZ                       ( 72000000UL )
#define configTICK_RATE_HZ                       ((TickType_t)1000)

/* ===================== 任务与内存配置 ===================== */
#define configMAX_PRIORITIES                     ( 5 )
#define configMINIMAL_STACK_SIZE                 ((uint16_t)64)  /* 256字节，测完高水位再调 */
#define configMAX_TASK_NAME_LEN                  ( 10 )
#define configMESSAGE_BUFFER_LENGTH_TYPE         uint8_t
#define configSUPPORT_STATIC_ALLOCATION          1
#define configSUPPORT_DYNAMIC_ALLOCATION         0
#define configTOTAL_HEAP_SIZE                    ((size_t)0)     /* 动态分配关闭，堆为0 */
#define configAPPLICATION_ALLOCATED_HEAP         0

/* ===================== 内核功能开关 ===================== */
#define configUSE_MUTEXES                        1
#define configUSE_RECURSIVE_MUTEXES              0
#define configUSE_COUNTING_SEMAPHORES            1
#define configUSE_TASK_NOTIFICATIONS             1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES    1
#define configUSE_QUEUE_SETS                     0
#define configQUEUE_REGISTRY_SIZE                0

/* ===================== 软件定时器配置 ===================== */
/* 如果你没用到 xTimerCreate/xTimerStart，建议关闭，释放~400字节RAM */
#define configUSE_TIMERS                         0
#if (configUSE_TIMERS == 1)
#define configTIMER_TASK_PRIORITY                ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH                 4
#define configTIMER_TASK_STACK_DEPTH             configMINIMAL_STACK_SIZE
#endif

#define configUSE_CO_ROUTINES                    0
#define configMAX_CO_ROUTINE_PRIORITIES          ( 2 )

/* ===================== 中断优先级配置 ===================== */
#ifdef __NVIC_PRIO_BITS
 #define configPRIO_BITS         __NVIC_PRIO_BITS
#else
 #define configPRIO_BITS         2
#endif

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY        3
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY   1
#define configKERNEL_INTERRUPT_PRIORITY        ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY   ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* ===================== 调试与断言 ===================== */
#define configCHECK_FOR_STACK_OVERFLOW         2  /* 开启栈溢出检测，方法2开销小 */
#define configUSE_MALLOC_FAILED_HOOK           0
#define configASSERT( x ) if ((x) == 0) {taskDISABLE_INTERRUPTS(); for( ;; );}
#define configUSE_TRACE_FACILITY               0
#define configGENERATE_RUN_TIME_STATS          0
#define configUSE_STATS_FORMATTING_FUNCTIONS   0

/* ===================== API 函数裁剪 ===================== */
#define INCLUDE_vTaskPrioritySet               0  /* 不用就关 */
#define INCLUDE_uxTaskPriorityGet              0  /* 不用就关 */
#define INCLUDE_vTaskDelete                    0  /* 不用就关 */
#define INCLUDE_vTaskCleanUpResources          0
#define INCLUDE_vTaskSuspend                   1
#define INCLUDE_vTaskDelayUntil                1
#define INCLUDE_vTaskDelay                     1
#define INCLUDE_xTaskGetSchedulerState         1
#define INCLUDE_xTaskGetCurrentTaskHandle      1
#define INCLUDE_uxTaskGetStackHighWaterMark    1  /* 必须开，用来测栈 */
#define INCLUDE_xTimerPendFunctionCall         0

/* ===================== 中断函数重映射 ===================== */
#define vPortSVCHandler        SVC_Handler
#define xPortPendSVHandler     PendSV_Handler
#define xPortSysTickHandler    SysTick_Handler

#define traceISR_ENTER()
#define traceISR_EXIT()
#define traceISR_EXIT_TO_SCHEDULER()

#endif /* FREERTOS_CONFIG_H */

