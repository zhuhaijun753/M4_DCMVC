/* generated messaging header file - do not edit */
#ifndef SF_MESSAGE_PORT_H_
#define SF_MESSAGE_PORT_H_
typedef enum e_sf_message_event_class
{
    SF_MESSAGE_EVENT_CLASS_TOUCH, /* Touch */
    SF_MESSAGE_EVENT_CLASS_PWM_DATA, /* PWM_data */
    SF_MESSAGE_EVENT_CLASS_HALL_EFFECT_FEEDBACK, /* Hall_effect_feedback */
    SF_MESSAGE_EVENT_CLASS_DIAGNOSTICS_DATA, /* Diagnostics_data */
} sf_message_event_class_t;
typedef enum e_sf_message_event
{
    SF_MESSAGE_EVENT_UNUSED, /* Unused */
    SF_MESSAGE_EVENT_NEW_DATA, /* New Data */
    SF_MESSAGE_EVENT_UPDATE_DUTY_CYCLE, /* Update duty cycle */
    SF_MESSAGE_EVENT_HALL_EFFECT_RPMS_MESSAGE, /* Hall effect rpms message */
    SF_MESSAGE_EVENT_BATTERY_SHORTCUT, /* Battery shortcut */
    SF_MESSAGE_EVENT_GROUND_SHORTCUT, /* Ground shortcut */
} sf_message_event_t;
extern TX_QUEUE main_thread_message_queue;
#endif /* SF_MESSAGE_PORT_H_ */
