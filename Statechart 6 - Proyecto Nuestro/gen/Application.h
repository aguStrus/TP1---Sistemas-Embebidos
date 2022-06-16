
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "..\inc\sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'application'.
*/

/*! Define dimension of the state configuration vector for orthogonal states. */
#define APPLICATION_MAX_ORTHOGONAL_STATES 3

/*! Define maximum number of time events that can be active at once */
#define APPLICATION_MAX_PARALLEL_TIME_EVENTS 2

/*! Define indices of states in the StateConfVector */
#define SCVI_APPLICATION_TECX_DEBOUNCE 0
#define SCVI_APPLICATION_TECX_NO_OPRIMIDO 0
#define SCVI_APPLICATION_TECX_OPRIMIDO 0
#define SCVI_APPLICATION_TECX_VALIDACION 0
#define SCVI_APPLICATION_MAIN_REGION_ESPERA 1
#define SCVI_APPLICATION_LED3_TITILA 2
#define SCVI_APPLICATION_LED3_TITILA_R1_ENCENDIDO 2
#define SCVI_APPLICATION_LED3_TITILA_R1_APAGADO 2
#define SCVI_APPLICATION_LED3_REPOSO 2

/*! Enumeration of all states */ 
typedef enum
{
	Application_last_state,
	Application_TECX_DEBOUNCE,
	Application_TECX_NO_OPRIMIDO,
	Application_TECX_OPRIMIDO,
	Application_TECX_VALIDACION,
	Application_main_region_ESPERA,
	Application_LED3_TITILA,
	Application_LED3_TITILA_r1_ENCENDIDO,
	Application_LED3_TITILA_r1_APAGADO,
	Application_LED3_REPOSO
} ApplicationStates;

/*! Type definition of the data structure for the ApplicationIface interface scope. */
typedef struct
{
	sc_boolean evTECXNoOprimido_raised;
	sc_boolean evTECXOprimido_raised;
	sc_integer evTECXOprimido_value;
} ApplicationIface;


/* Declaration of constants for scope ApplicationIface. */
extern const sc_integer APPLICATION_APPLICATIONIFACE_LED1;
extern const sc_integer APPLICATION_APPLICATIONIFACE_LED2;
extern const sc_integer APPLICATION_APPLICATIONIFACE_LED3;
extern const sc_boolean APPLICATION_APPLICATIONIFACE_LED_ON;
extern const sc_boolean APPLICATION_APPLICATIONIFACE_LED_OFF;
extern const sc_integer APPLICATION_APPLICATIONIFACE_TEC1;
extern const sc_integer APPLICATION_APPLICATIONIFACE_TEC2;
extern const sc_integer APPLICATION_APPLICATIONIFACE_TEC3;
extern const sc_integer APPLICATION_APPLICATIONIFACE_TEC4;


/*! Type definition of the data structure for the ApplicationInternal interface scope. */
typedef struct
{
	sc_boolean siTitilarLED_raised;
	sc_boolean siNoTitilarLED_raised;
	sc_boolean siTECXOK_raised;
	sc_integer viTecla;
} ApplicationInternal;



/*! Type definition of the data structure for the ApplicationTimeEvents interface scope. */
typedef struct
{
	sc_boolean application_TECX_DEBOUNCE_tev0_raised;
	sc_boolean application_LED3_TITILA_r1_ENCENDIDO_tev0_raised;
	sc_boolean application_LED3_TITILA_r1_APAGADO_tev0_raised;
} ApplicationTimeEvents;




/*! 
 * Type definition of the data structure for the Application state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	ApplicationStates stateConfVector[APPLICATION_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	ApplicationIface iface;
	ApplicationInternal internal;
	ApplicationTimeEvents timeEvents;
} Application;



/*! Initializes the Application state machine data structures. Must be called before first usage.*/
extern void application_init(Application* handle);

/*! Activates the state machine */
extern void application_enter(Application* handle);

/*! Deactivates the state machine */
extern void application_exit(Application* handle);

/*! Performs a 'run to completion' step. */
extern void application_runCycle(Application* handle);

/*! Raises a time event. */
extern void application_raiseTimeEvent(Application* handle, sc_eventid evid);

/*! Raises the in event 'evTECXNoOprimido' that is defined in the default interface scope. */ 
extern void applicationIface_raise_evTECXNoOprimido(Application* handle);

/*! Raises the in event 'evTECXOprimido' that is defined in the default interface scope. */ 
extern void applicationIface_raise_evTECXOprimido(Application* handle, sc_integer value);

/*! Gets the value of the variable 'LED1' that is defined in the default interface scope. */ 
extern const sc_integer applicationIface_get_lED1(const Application* handle);
/*! Gets the value of the variable 'LED2' that is defined in the default interface scope. */ 
extern const sc_integer applicationIface_get_lED2(const Application* handle);
/*! Gets the value of the variable 'LED3' that is defined in the default interface scope. */ 
extern const sc_integer applicationIface_get_lED3(const Application* handle);
/*! Gets the value of the variable 'LED_ON' that is defined in the default interface scope. */ 
extern const sc_boolean applicationIface_get_lED_ON(const Application* handle);
/*! Gets the value of the variable 'LED_OFF' that is defined in the default interface scope. */ 
extern const sc_boolean applicationIface_get_lED_OFF(const Application* handle);
/*! Gets the value of the variable 'TEC1' that is defined in the default interface scope. */ 
extern const sc_integer applicationIface_get_tEC1(const Application* handle);
/*! Gets the value of the variable 'TEC2' that is defined in the default interface scope. */ 
extern const sc_integer applicationIface_get_tEC2(const Application* handle);
/*! Gets the value of the variable 'TEC3' that is defined in the default interface scope. */ 
extern const sc_integer applicationIface_get_tEC3(const Application* handle);
/*! Gets the value of the variable 'TEC4' that is defined in the default interface scope. */ 
extern const sc_integer applicationIface_get_tEC4(const Application* handle);

/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean application_isActive(const Application* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean application_isFinal(const Application* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean application_isStateActive(const Application* handle, ApplicationStates state);


#ifdef __cplusplus
}
#endif 

#endif /* APPLICATION_H_ */
