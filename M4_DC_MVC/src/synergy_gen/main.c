/* generated main source file - do not edit */
#include "bsp_api.h"
#include "tx_api.h"

extern void blinky_thread_create(void);
extern void usb_console_thread_create(void);
extern void pwm_thread_create(void);
extern void adc_thread_create(void);
extern void diagnostics_thread_create(void);
extern void hall_effect_thread_create(void);
extern void main_thread_create(void);

uint32_t g_ssp_common_thread_count;
bool g_ssp_common_initialized;
TX_SEMAPHORE g_ssp_common_initialized_semaphore;

#if defined(__ICCARM__)
#define WEAK_REF_ATTRIBUTE
#pragma weak tx_application_define_user               = tx_application_define_internal
#elif defined(__GNUC__)
#define WEAK_REF_ATTRIBUTE      __attribute__ ((weak, alias("tx_application_define_internal")))
#endif

#ifdef TX_USER_TRACE_BUFFER_DECLARE
TX_USER_TRACE_BUFFER_DECLARE;
#endif

void g_hal_init(void);

/** Weak reference for tx_err_callback */
#if defined(__ICCARM__)
#define tx_startup_err_callback_WEAK_ATTRIBUTE
#pragma weak tx_startup_err_callback  = tx_startup_err_callback_internal
#elif defined(__GNUC__)
#define tx_startup_err_callback_WEAK_ATTRIBUTE __attribute__ ((weak, alias("tx_startup_err_callback_internal")))
#endif
void tx_startup_err_callback_internal(void *p_instance, void *p_data);
void tx_startup_err_callback(void *p_instance, void *p_data)
tx_startup_err_callback_WEAK_ATTRIBUTE;

void tx_application_define_internal(void *first_unused_memory);

void tx_application_define_internal(void *first_unused_memory)
{
    /* Does nothing. Default implementation of tx_application_define_user(). */
    SSP_PARAMETER_NOT_USED (first_unused_memory);
}

void tx_application_define_internal(void *first_unused_memory);
void tx_application_define_user(void *first_unused_memory)
WEAK_REF_ATTRIBUTE;

void tx_application_define(void *first_unused_memory)
{
    g_ssp_common_thread_count = 0;
    g_ssp_common_initialized = false;

    /* Create semaphore to make sure common init is done before threads start running. */
    UINT err;
    err = tx_semaphore_create (&g_ssp_common_initialized_semaphore, "SSP Common Init Sem", 1);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&g_ssp_common_initialized_semaphore, 0);
    }

    blinky_thread_create ();
    usb_console_thread_create ();
    pwm_thread_create ();
    adc_thread_create ();
    diagnostics_thread_create ();
    hall_effect_thread_create ();
    main_thread_create ();

#ifdef TX_USER_ENABLE_TRACE
    TX_USER_ENABLE_TRACE;
#endif

    tx_application_define_user (first_unused_memory);
}

/*********************************************************************************************************************
 * @brief      This is a weak example initialization error function.  It should be overridden by defining a user function
 *             with the prototype below.
 *             - void tx_startup_err_callback(void * p_instance, void * p_data)
 *
 * @param[in]  p_instance arguments used to identify which instance caused the error and p_data Callback arguments used to identify what error caused the callback.
 **********************************************************************************************************************/
void tx_startup_err_callback_internal(void *p_instance, void *p_data);
void tx_startup_err_callback_internal(void *p_instance, void *p_data)
{
    /** Suppress compiler warning for not using parameters. */
    SSP_PARAMETER_NOT_USED (p_instance);
    SSP_PARAMETER_NOT_USED (p_data);

    /** An error has occurred. Please check function arguments for more information. */
    BSP_CFG_HANDLE_UNRECOVERABLE_ERROR (0);
}

void tx_startup_common_init(void);
void tx_startup_common_init(void)
{
    /* First thread will take care of common initialization. */
    UINT err;
    err = tx_semaphore_get (&g_ssp_common_initialized_semaphore, TX_WAIT_FOREVER);

    if (TX_SUCCESS != err)
    {
        /* Check err, problem occurred. */
        tx_startup_err_callback (&g_ssp_common_initialized_semaphore, 0);
    }

    /* Only perform common initialization if this is the first thread to execute. */
    if (false == g_ssp_common_initialized)
    {
        /* Later threads will not run this code. */
        g_ssp_common_initialized = true;

        /* Perform common module initialization. */
        g_hal_init ();

        /* Now that common initialization is done, let other threads through. */
        /* First decrement by 1 since 1 thread has already come through. */
        g_ssp_common_thread_count--;
        while (g_ssp_common_thread_count > 0)
        {
            err = tx_semaphore_put (&g_ssp_common_initialized_semaphore);

            if (TX_SUCCESS != err)
            {
                /* Check err, problem occurred. */
                tx_startup_err_callback (&g_ssp_common_initialized_semaphore, 0);
            }

            g_ssp_common_thread_count--;
        }
    }
}

int main(void)
{
    __disable_irq ();
    tx_kernel_enter ();

    return 0;
}
