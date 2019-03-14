/* generated messaging source file - do not edit */
#include "sf_message.h"
#ifndef SF_MESSAGE_CFG_QUEUE_SIZE
#define SF_MESSAGE_CFG_QUEUE_SIZE (16)
#endif
TX_QUEUE main_thread_message_queue;
static uint8_t queue_memory_main_thread_message_queue[SF_MESSAGE_CFG_QUEUE_SIZE];
static sf_message_subscriber_t main_thread_message_queue_0_0 =
{ .p_queue = &main_thread_message_queue, .instance_range =
{ .start = 0, .end = 0 } };
static sf_message_subscriber_t *gp_group_SF_MESSAGE_EVENT_CLASS_TOUCH[] =
{ &main_thread_message_queue_0_0, };
static sf_message_subscriber_list_t g_list_SF_MESSAGE_EVENT_CLASS_TOUCH =
{ .event_class = SF_MESSAGE_EVENT_CLASS_TOUCH, .number_of_nodes = 1, .pp_subscriber_group =
          gp_group_SF_MESSAGE_EVENT_CLASS_TOUCH };
static sf_message_subscriber_t *gp_group_SF_MESSAGE_EVENT_CLASS_PWM_DATA[] =
{ &main_thread_message_queue_0_0, };
static sf_message_subscriber_list_t g_list_SF_MESSAGE_EVENT_CLASS_PWM_DATA =
{ .event_class = SF_MESSAGE_EVENT_CLASS_PWM_DATA, .number_of_nodes = 1, .pp_subscriber_group =
          gp_group_SF_MESSAGE_EVENT_CLASS_PWM_DATA };
static sf_message_subscriber_t *gp_group_SF_MESSAGE_EVENT_CLASS_HALL_EFFECT_FEEDBACK[] =
{ &main_thread_message_queue_0_0, };
static sf_message_subscriber_list_t g_list_SF_MESSAGE_EVENT_CLASS_HALL_EFFECT_FEEDBACK =
{ .event_class = SF_MESSAGE_EVENT_CLASS_HALL_EFFECT_FEEDBACK, .number_of_nodes = 1, .pp_subscriber_group =
          gp_group_SF_MESSAGE_EVENT_CLASS_HALL_EFFECT_FEEDBACK };
static sf_message_subscriber_t *gp_group_SF_MESSAGE_EVENT_CLASS_DIAGNOSTICS_DATA[] =
{ &main_thread_message_queue_0_0, };
static sf_message_subscriber_list_t g_list_SF_MESSAGE_EVENT_CLASS_DIAGNOSTICS_DATA =
{ .event_class = SF_MESSAGE_EVENT_CLASS_DIAGNOSTICS_DATA, .number_of_nodes = 1, .pp_subscriber_group =
          gp_group_SF_MESSAGE_EVENT_CLASS_DIAGNOSTICS_DATA };
sf_message_subscriber_list_t *p_subscriber_lists[] =
{ &g_list_SF_MESSAGE_EVENT_CLASS_TOUCH,
  &g_list_SF_MESSAGE_EVENT_CLASS_PWM_DATA,
  &g_list_SF_MESSAGE_EVENT_CLASS_HALL_EFFECT_FEEDBACK,
  &g_list_SF_MESSAGE_EVENT_CLASS_DIAGNOSTICS_DATA,
  NULL };
void g_message_init(void);
void g_message_init(void)
{
    tx_queue_create (&main_thread_message_queue, (CHAR *) "Main Thread Message Queue", 1,
                     &queue_memory_main_thread_message_queue, sizeof(queue_memory_main_thread_message_queue));
}