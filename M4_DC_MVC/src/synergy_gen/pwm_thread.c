/* generated thread source file - do not edit */
#include "pwm_thread.h"

TX_THREAD pwm_thread;
void pwm_thread_create(void);
static void pwm_thread_func(ULONG thread_input);
static uint8_t pwm_thread_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.pwm_thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_QUEUE g_cdc_to_pwm_queue;
static uint8_t queue_memory_g_cdc_to_pwm_queue[100];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void pwm_thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_g_cdc_to_pwm_queue;
    err_g_cdc_to_pwm_queue = tx_queue_create (&g_cdc_to_pwm_queue, (CHAR *) "PWM Queue", 1,
                                              &queue_memory_g_cdc_to_pwm_queue,
                                              sizeof(queue_memory_g_cdc_to_pwm_queue));
    if (TX_SUCCESS != err_g_cdc_to_pwm_queue)
    {
        tx_startup_err_callback (&g_cdc_to_pwm_queue, 0);
    }

    UINT err;
    err = tx_thread_create (&pwm_thread, (CHAR *) "PWM", pwm_thread_func, (ULONG) NULL, &pwm_thread_stack, 1024, 5, 5,
                            1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&pwm_thread, 0);
    }
}

static void pwm_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    pwm_thread_entry ();
}