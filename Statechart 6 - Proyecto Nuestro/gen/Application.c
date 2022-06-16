
#include "Application.h"
#include "..\inc\sc_types.h"
#include "ApplicationRequired.h"

#include <stdlib.h>
#include <string.h>
/*! \file Implementation of the state machine 'application'
*/

/* prototypes of all internal functions */
static sc_boolean check_TECX_DEBOUNCE_tr0_tr0(const Application* handle);
static sc_boolean check_TECX_NO_OPRIMIDO_tr0_tr0(const Application* handle);
static sc_boolean check_TECX_OPRIMIDO_tr0_tr0(const Application* handle);
static sc_boolean check_TECX_VALIDACION_tr0_tr0(const Application* handle);
static sc_boolean check_TECX_VALIDACION_tr1_tr1(const Application* handle);
static sc_boolean check_main_region_ESPERA_tr0_tr0(const Application* handle);
static sc_boolean check_main_region_ESPERA_tr1_tr1(const Application* handle);
static sc_boolean check_main_region_ESPERA_tr2_tr2(const Application* handle);
static sc_boolean check_main_region_ESPERA_tr3_tr3(const Application* handle);
static sc_boolean check_LED3_TITILA_tr0_tr0(const Application* handle);
static sc_boolean check_LED3_TITILA_r1_ENCENDIDO_tr0_tr0(const Application* handle);
static sc_boolean check_LED3_TITILA_r1_APAGADO_tr0_tr0(const Application* handle);
static sc_boolean check_LED3_REPOSO_tr0_tr0(const Application* handle);
static void effect_TECX_DEBOUNCE_tr0(Application* handle);
static void effect_TECX_NO_OPRIMIDO_tr0(Application* handle);
static void effect_TECX_OPRIMIDO_tr0(Application* handle);
static void effect_TECX_VALIDACION_tr0(Application* handle);
static void effect_TECX_VALIDACION_tr1(Application* handle);
static void effect_main_region_ESPERA_tr0(Application* handle);
static void effect_main_region_ESPERA_tr1(Application* handle);
static void effect_main_region_ESPERA_tr2(Application* handle);
static void effect_main_region_ESPERA_tr3(Application* handle);
static void effect_LED3_TITILA_tr0(Application* handle);
static void effect_LED3_TITILA_r1_ENCENDIDO_tr0(Application* handle);
static void effect_LED3_TITILA_r1_APAGADO_tr0(Application* handle);
static void effect_LED3_REPOSO_tr0(Application* handle);
static void enact_TECX_DEBOUNCE(Application* handle);
static void enact_TECX_OPRIMIDO(Application* handle);
static void enact_LED3_TITILA_r1_ENCENDIDO(Application* handle);
static void enact_LED3_TITILA_r1_APAGADO(Application* handle);
static void enact_LED3_REPOSO(Application* handle);
static void exact_TECX_DEBOUNCE(Application* handle);
static void exact_LED3_TITILA_r1_ENCENDIDO(Application* handle);
static void exact_LED3_TITILA_r1_APAGADO(Application* handle);
static void enseq_TECX_DEBOUNCE_default(Application* handle);
static void enseq_TECX_NO_OPRIMIDO_default(Application* handle);
static void enseq_TECX_OPRIMIDO_default(Application* handle);
static void enseq_TECX_VALIDACION_default(Application* handle);
static void enseq_main_region_ESPERA_default(Application* handle);
static void enseq_LED3_TITILA_default(Application* handle);
static void enseq_LED3_TITILA_r1_ENCENDIDO_default(Application* handle);
static void enseq_LED3_TITILA_r1_APAGADO_default(Application* handle);
static void enseq_LED3_REPOSO_default(Application* handle);
static void enseq_TECX_default(Application* handle);
static void enseq_main_region_default(Application* handle);
static void enseq_LED3_default(Application* handle);
static void enseq_LED3_TITILA_r1_default(Application* handle);
static void exseq_TECX_DEBOUNCE(Application* handle);
static void exseq_TECX_NO_OPRIMIDO(Application* handle);
static void exseq_TECX_OPRIMIDO(Application* handle);
static void exseq_TECX_VALIDACION(Application* handle);
static void exseq_main_region_ESPERA(Application* handle);
static void exseq_LED3_TITILA(Application* handle);
static void exseq_LED3_TITILA_r1_ENCENDIDO(Application* handle);
static void exseq_LED3_TITILA_r1_APAGADO(Application* handle);
static void exseq_LED3_REPOSO(Application* handle);
static void exseq_TECX(Application* handle);
static void exseq_main_region(Application* handle);
static void exseq_LED3(Application* handle);
static void exseq_LED3_TITILA_r1(Application* handle);
static void react_TECX_DEBOUNCE(Application* handle);
static void react_TECX_NO_OPRIMIDO(Application* handle);
static void react_TECX_OPRIMIDO(Application* handle);
static void react_TECX_VALIDACION(Application* handle);
static void react_main_region_ESPERA(Application* handle);
static void react_LED3_TITILA_r1_ENCENDIDO(Application* handle);
static void react_LED3_TITILA_r1_APAGADO(Application* handle);
static void react_LED3_REPOSO(Application* handle);
static void react_TECX__entry_Default(Application* handle);
static void react_main_region__entry_Default(Application* handle);
static void react_LED3_TITILA_r1__entry_Default(Application* handle);
static void react_LED3__entry_Default(Application* handle);
static void clearInEvents(Application* handle);
static void clearOutEvents(Application* handle);

const sc_integer APPLICATION_APPLICATIONIFACE_LED1 = 3;
const sc_integer APPLICATION_APPLICATIONIFACE_LED2 = 4;
const sc_integer APPLICATION_APPLICATIONIFACE_LED3 = 5;
const sc_boolean APPLICATION_APPLICATIONIFACE_LED_ON = bool_true;
const sc_boolean APPLICATION_APPLICATIONIFACE_LED_OFF = bool_false;
const sc_integer APPLICATION_APPLICATIONIFACE_TEC1 = 1 << 0;
const sc_integer APPLICATION_APPLICATIONIFACE_TEC2 = 1 << 1;
const sc_integer APPLICATION_APPLICATIONIFACE_TEC3 = 1 << 2;
const sc_integer APPLICATION_APPLICATIONIFACE_TEC4 = 1 << 3;

void application_init(Application* handle)
{
		sc_integer i;
	
		for (i = 0; i < APPLICATION_MAX_ORTHOGONAL_STATES; ++i)
		{
			handle->stateConfVector[i] = Application_last_state;
		}
		
		
		handle->stateConfVectorPosition = 0;
	
		clearInEvents(handle);
		clearOutEvents(handle);
	
		/* Default init sequence for statechart application */
		handle->internal.viTecla = 0;
}

void application_enter(Application* handle)
{
	/* Default enter sequence for statechart application */
	enseq_TECX_default(handle);
	enseq_main_region_default(handle);
	enseq_LED3_default(handle);
}

void application_runCycle(Application* handle)
{
	clearOutEvents(handle);
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < APPLICATION_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case Application_TECX_DEBOUNCE:
		{
			react_TECX_DEBOUNCE(handle);
			break;
		}
		case Application_TECX_NO_OPRIMIDO:
		{
			react_TECX_NO_OPRIMIDO(handle);
			break;
		}
		case Application_TECX_OPRIMIDO:
		{
			react_TECX_OPRIMIDO(handle);
			break;
		}
		case Application_TECX_VALIDACION:
		{
			react_TECX_VALIDACION(handle);
			break;
		}
		case Application_main_region_ESPERA:
		{
			react_main_region_ESPERA(handle);
			break;
		}
		case Application_LED3_TITILA_r1_ENCENDIDO:
		{
			react_LED3_TITILA_r1_ENCENDIDO(handle);
			break;
		}
		case Application_LED3_TITILA_r1_APAGADO:
		{
			react_LED3_TITILA_r1_APAGADO(handle);
			break;
		}
		case Application_LED3_REPOSO:
		{
			react_LED3_REPOSO(handle);
			break;
		}
		default:
			break;
		}
	}
	
	clearInEvents(handle);
}

void application_exit(Application* handle)
{
	/* Default exit sequence for statechart application */
	exseq_TECX(handle);
	exseq_main_region(handle);
	exseq_LED3(handle);
}

sc_boolean application_isActive(const Application* handle)
{
	sc_boolean result = bool_false;
	int i;
	
	for(i = 0; i < APPLICATION_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != Application_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean application_isFinal(const Application* handle)
{
   return bool_false;
}

void application_raiseTimeEvent(Application* handle, sc_eventid evid)
{
	if ( ((sc_intptr_t)evid) >= ((sc_intptr_t)&(handle->timeEvents))
		&&  ((sc_intptr_t)evid) < ((sc_intptr_t)&(handle->timeEvents)) + sizeof(ApplicationTimeEvents))
		{
		*(sc_boolean*)evid = bool_true;
	}		
}

sc_boolean application_isStateActive(const Application* handle, ApplicationStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Application_TECX_DEBOUNCE :
			result = (sc_boolean) (handle->stateConfVector[SCVI_APPLICATION_TECX_DEBOUNCE] == Application_TECX_DEBOUNCE
			);
			break;
		case Application_TECX_NO_OPRIMIDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_APPLICATION_TECX_NO_OPRIMIDO] == Application_TECX_NO_OPRIMIDO
			);
			break;
		case Application_TECX_OPRIMIDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_APPLICATION_TECX_OPRIMIDO] == Application_TECX_OPRIMIDO
			);
			break;
		case Application_TECX_VALIDACION :
			result = (sc_boolean) (handle->stateConfVector[SCVI_APPLICATION_TECX_VALIDACION] == Application_TECX_VALIDACION
			);
			break;
		case Application_main_region_ESPERA :
			result = (sc_boolean) (handle->stateConfVector[SCVI_APPLICATION_MAIN_REGION_ESPERA] == Application_main_region_ESPERA
			);
			break;
		case Application_LED3_TITILA :
			result = (sc_boolean) (handle->stateConfVector[SCVI_APPLICATION_LED3_TITILA] >= Application_LED3_TITILA
				&& handle->stateConfVector[SCVI_APPLICATION_LED3_TITILA] <= Application_LED3_TITILA_r1_APAGADO);
			break;
		case Application_LED3_TITILA_r1_ENCENDIDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_APPLICATION_LED3_TITILA_R1_ENCENDIDO] == Application_LED3_TITILA_r1_ENCENDIDO
			);
			break;
		case Application_LED3_TITILA_r1_APAGADO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_APPLICATION_LED3_TITILA_R1_APAGADO] == Application_LED3_TITILA_r1_APAGADO
			);
			break;
		case Application_LED3_REPOSO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_APPLICATION_LED3_REPOSO] == Application_LED3_REPOSO
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}

static void clearInEvents(Application* handle)
{
	handle->iface.evTECXNoOprimido_raised = bool_false;
	handle->iface.evTECXOprimido_raised = bool_false;
	handle->internal.siTitilarLED_raised = bool_false;
	handle->internal.siNoTitilarLED_raised = bool_false;
	handle->internal.siTECXOK_raised = bool_false;
	handle->timeEvents.application_TECX_DEBOUNCE_tev0_raised = bool_false;
	handle->timeEvents.application_LED3_TITILA_r1_ENCENDIDO_tev0_raised = bool_false;
	handle->timeEvents.application_LED3_TITILA_r1_APAGADO_tev0_raised = bool_false;
}

static void clearOutEvents(Application* handle)
{
}

void applicationIface_raise_evTECXNoOprimido(Application* handle)
{
	handle->iface.evTECXNoOprimido_raised = bool_true;
}
void applicationIface_raise_evTECXOprimido(Application* handle, sc_integer value)
{
	handle->iface.evTECXOprimido_value = value;
	handle->iface.evTECXOprimido_raised = bool_true;
}


const sc_integer applicationIface_get_lED1(const Application* handle)
{
	return APPLICATION_APPLICATIONIFACE_LED1;
}
const sc_integer applicationIface_get_lED2(const Application* handle)
{
	return APPLICATION_APPLICATIONIFACE_LED2;
}
const sc_integer applicationIface_get_lED3(const Application* handle)
{
	return APPLICATION_APPLICATIONIFACE_LED3;
}
const sc_boolean applicationIface_get_lED_ON(const Application* handle)
{
	return APPLICATION_APPLICATIONIFACE_LED_ON;
}
const sc_boolean applicationIface_get_lED_OFF(const Application* handle)
{
	return APPLICATION_APPLICATIONIFACE_LED_OFF;
}
const sc_integer applicationIface_get_tEC1(const Application* handle)
{
	return APPLICATION_APPLICATIONIFACE_TEC1;
}
const sc_integer applicationIface_get_tEC2(const Application* handle)
{
	return APPLICATION_APPLICATIONIFACE_TEC2;
}
const sc_integer applicationIface_get_tEC3(const Application* handle)
{
	return APPLICATION_APPLICATIONIFACE_TEC3;
}
const sc_integer applicationIface_get_tEC4(const Application* handle)
{
	return APPLICATION_APPLICATIONIFACE_TEC4;
}

/* implementations of all internal functions */

static sc_boolean check_TECX_DEBOUNCE_tr0_tr0(const Application* handle)
{
	return handle->timeEvents.application_TECX_DEBOUNCE_tev0_raised;
}

static sc_boolean check_TECX_NO_OPRIMIDO_tr0_tr0(const Application* handle)
{
	return handle->iface.evTECXOprimido_raised;
}

static sc_boolean check_TECX_OPRIMIDO_tr0_tr0(const Application* handle)
{
	return handle->iface.evTECXNoOprimido_raised;
}

static sc_boolean check_TECX_VALIDACION_tr0_tr0(const Application* handle)
{
	return handle->iface.evTECXOprimido_raised;
}

static sc_boolean check_TECX_VALIDACION_tr1_tr1(const Application* handle)
{
	return handle->iface.evTECXNoOprimido_raised;
}

static sc_boolean check_main_region_ESPERA_tr0_tr0(const Application* handle)
{
	return ((handle->internal.siTECXOK_raised) && (handle->internal.viTecla == APPLICATION_APPLICATIONIFACE_TEC4)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_ESPERA_tr1_tr1(const Application* handle)
{
	return ((handle->internal.siTECXOK_raised) && (handle->internal.viTecla == APPLICATION_APPLICATIONIFACE_TEC3)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_ESPERA_tr2_tr2(const Application* handle)
{
	return ((handle->internal.siTECXOK_raised) && (handle->internal.viTecla == APPLICATION_APPLICATIONIFACE_TEC2)) ? bool_true : bool_false;
}

static sc_boolean check_main_region_ESPERA_tr3_tr3(const Application* handle)
{
	return ((handle->internal.siTECXOK_raised) && (handle->internal.viTecla == APPLICATION_APPLICATIONIFACE_TEC1)) ? bool_true : bool_false;
}

static sc_boolean check_LED3_TITILA_tr0_tr0(const Application* handle)
{
	return handle->internal.siNoTitilarLED_raised;
}

static sc_boolean check_LED3_TITILA_r1_ENCENDIDO_tr0_tr0(const Application* handle)
{
	return handle->timeEvents.application_LED3_TITILA_r1_ENCENDIDO_tev0_raised;
}

static sc_boolean check_LED3_TITILA_r1_APAGADO_tr0_tr0(const Application* handle)
{
	return handle->timeEvents.application_LED3_TITILA_r1_APAGADO_tev0_raised;
}

static sc_boolean check_LED3_REPOSO_tr0_tr0(const Application* handle)
{
	return handle->internal.siTitilarLED_raised;
}

static void effect_TECX_DEBOUNCE_tr0(Application* handle)
{
	exseq_TECX_DEBOUNCE(handle);
	enseq_TECX_VALIDACION_default(handle);
}

static void effect_TECX_NO_OPRIMIDO_tr0(Application* handle)
{
	exseq_TECX_NO_OPRIMIDO(handle);
	enseq_TECX_DEBOUNCE_default(handle);
}

static void effect_TECX_OPRIMIDO_tr0(Application* handle)
{
	exseq_TECX_OPRIMIDO(handle);
	enseq_TECX_NO_OPRIMIDO_default(handle);
}

static void effect_TECX_VALIDACION_tr0(Application* handle)
{
	exseq_TECX_VALIDACION(handle);
	enseq_TECX_OPRIMIDO_default(handle);
}

static void effect_TECX_VALIDACION_tr1(Application* handle)
{
	exseq_TECX_VALIDACION(handle);
	enseq_TECX_NO_OPRIMIDO_default(handle);
}

static void effect_main_region_ESPERA_tr0(Application* handle)
{
	exseq_main_region_ESPERA(handle);
	handle->internal.siTitilarLED_raised = bool_true;
	enseq_main_region_ESPERA_default(handle);
}

static void effect_main_region_ESPERA_tr1(Application* handle)
{
	exseq_main_region_ESPERA(handle);
	applicationIface_opLED(handle, APPLICATION_APPLICATIONIFACE_LED2, APPLICATION_APPLICATIONIFACE_LED_ON);
	enseq_main_region_ESPERA_default(handle);
}

static void effect_main_region_ESPERA_tr2(Application* handle)
{
	exseq_main_region_ESPERA(handle);
	applicationIface_opLED(handle, APPLICATION_APPLICATIONIFACE_LED1, APPLICATION_APPLICATIONIFACE_LED_ON);
	enseq_main_region_ESPERA_default(handle);
}

static void effect_main_region_ESPERA_tr3(Application* handle)
{
	exseq_main_region_ESPERA(handle);
	applicationIface_opLED(handle, APPLICATION_APPLICATIONIFACE_LED1, APPLICATION_APPLICATIONIFACE_LED_OFF);
	applicationIface_opLED(handle, APPLICATION_APPLICATIONIFACE_LED2, APPLICATION_APPLICATIONIFACE_LED_OFF);
	applicationIface_opLED(handle, APPLICATION_APPLICATIONIFACE_LED3, APPLICATION_APPLICATIONIFACE_LED_OFF);
	handle->internal.siNoTitilarLED_raised = bool_true;
	enseq_main_region_ESPERA_default(handle);
}

static void effect_LED3_TITILA_tr0(Application* handle)
{
	exseq_LED3_TITILA(handle);
	enseq_LED3_REPOSO_default(handle);
}

static void effect_LED3_TITILA_r1_ENCENDIDO_tr0(Application* handle)
{
	exseq_LED3_TITILA_r1_ENCENDIDO(handle);
	enseq_LED3_TITILA_r1_APAGADO_default(handle);
}

static void effect_LED3_TITILA_r1_APAGADO_tr0(Application* handle)
{
	exseq_LED3_TITILA_r1_APAGADO(handle);
	enseq_LED3_TITILA_r1_ENCENDIDO_default(handle);
}

static void effect_LED3_REPOSO_tr0(Application* handle)
{
	exseq_LED3_REPOSO(handle);
	enseq_LED3_TITILA_default(handle);
}

/* Entry action for state 'DEBOUNCE'. */
static void enact_TECX_DEBOUNCE(Application* handle)
{
	/* Entry action for state 'DEBOUNCE'. */
	application_setTimer(handle, (sc_eventid) &(handle->timeEvents.application_TECX_DEBOUNCE_tev0_raised) , 100, bool_false);
}

/* Entry action for state 'OPRIMIDO'. */
static void enact_TECX_OPRIMIDO(Application* handle)
{
	/* Entry action for state 'OPRIMIDO'. */
	handle->internal.siTECXOK_raised = bool_true;
	handle->internal.viTecla = handle->iface.evTECXOprimido_value;
}

/* Entry action for state 'ENCENDIDO'. */
static void enact_LED3_TITILA_r1_ENCENDIDO(Application* handle)
{
	/* Entry action for state 'ENCENDIDO'. */
	application_setTimer(handle, (sc_eventid) &(handle->timeEvents.application_LED3_TITILA_r1_ENCENDIDO_tev0_raised) , 500, bool_false);
	applicationIface_opLED(handle, APPLICATION_APPLICATIONIFACE_LED3, APPLICATION_APPLICATIONIFACE_LED_ON);
}

/* Entry action for state 'APAGADO'. */
static void enact_LED3_TITILA_r1_APAGADO(Application* handle)
{
	/* Entry action for state 'APAGADO'. */
	application_setTimer(handle, (sc_eventid) &(handle->timeEvents.application_LED3_TITILA_r1_APAGADO_tev0_raised) , 250, bool_false);
	applicationIface_opLED(handle, APPLICATION_APPLICATIONIFACE_LED3, APPLICATION_APPLICATIONIFACE_LED_OFF);
}

/* Entry action for state 'REPOSO'. */
static void enact_LED3_REPOSO(Application* handle)
{
	/* Entry action for state 'REPOSO'. */
	applicationIface_opLED(handle, APPLICATION_APPLICATIONIFACE_LED3, APPLICATION_APPLICATIONIFACE_LED_OFF);
}

/* Exit action for state 'DEBOUNCE'. */
static void exact_TECX_DEBOUNCE(Application* handle)
{
	/* Exit action for state 'DEBOUNCE'. */
	application_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.application_TECX_DEBOUNCE_tev0_raised) );		
}

/* Exit action for state 'ENCENDIDO'. */
static void exact_LED3_TITILA_r1_ENCENDIDO(Application* handle)
{
	/* Exit action for state 'ENCENDIDO'. */
	application_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.application_LED3_TITILA_r1_ENCENDIDO_tev0_raised) );		
}

/* Exit action for state 'APAGADO'. */
static void exact_LED3_TITILA_r1_APAGADO(Application* handle)
{
	/* Exit action for state 'APAGADO'. */
	application_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.application_LED3_TITILA_r1_APAGADO_tev0_raised) );		
}

/* 'default' enter sequence for state DEBOUNCE */
static void enseq_TECX_DEBOUNCE_default(Application* handle)
{
	/* 'default' enter sequence for state DEBOUNCE */
	enact_TECX_DEBOUNCE(handle);
	handle->stateConfVector[0] = Application_TECX_DEBOUNCE;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state NO_OPRIMIDO */
static void enseq_TECX_NO_OPRIMIDO_default(Application* handle)
{
	/* 'default' enter sequence for state NO_OPRIMIDO */
	handle->stateConfVector[0] = Application_TECX_NO_OPRIMIDO;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state OPRIMIDO */
static void enseq_TECX_OPRIMIDO_default(Application* handle)
{
	/* 'default' enter sequence for state OPRIMIDO */
	enact_TECX_OPRIMIDO(handle);
	handle->stateConfVector[0] = Application_TECX_OPRIMIDO;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state VALIDACION */
static void enseq_TECX_VALIDACION_default(Application* handle)
{
	/* 'default' enter sequence for state VALIDACION */
	handle->stateConfVector[0] = Application_TECX_VALIDACION;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state ESPERA */
static void enseq_main_region_ESPERA_default(Application* handle)
{
	/* 'default' enter sequence for state ESPERA */
	handle->stateConfVector[1] = Application_main_region_ESPERA;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state TITILA */
static void enseq_LED3_TITILA_default(Application* handle)
{
	/* 'default' enter sequence for state TITILA */
	enseq_LED3_TITILA_r1_default(handle);
}

/* 'default' enter sequence for state ENCENDIDO */
static void enseq_LED3_TITILA_r1_ENCENDIDO_default(Application* handle)
{
	/* 'default' enter sequence for state ENCENDIDO */
	enact_LED3_TITILA_r1_ENCENDIDO(handle);
	handle->stateConfVector[2] = Application_LED3_TITILA_r1_ENCENDIDO;
	handle->stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state APAGADO */
static void enseq_LED3_TITILA_r1_APAGADO_default(Application* handle)
{
	/* 'default' enter sequence for state APAGADO */
	enact_LED3_TITILA_r1_APAGADO(handle);
	handle->stateConfVector[2] = Application_LED3_TITILA_r1_APAGADO;
	handle->stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state REPOSO */
static void enseq_LED3_REPOSO_default(Application* handle)
{
	/* 'default' enter sequence for state REPOSO */
	enact_LED3_REPOSO(handle);
	handle->stateConfVector[2] = Application_LED3_REPOSO;
	handle->stateConfVectorPosition = 2;
}

/* 'default' enter sequence for region TECX */
static void enseq_TECX_default(Application* handle)
{
	/* 'default' enter sequence for region TECX */
	react_TECX__entry_Default(handle);
}

/* 'default' enter sequence for region main region */
static void enseq_main_region_default(Application* handle)
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default(handle);
}

/* 'default' enter sequence for region LED3 */
static void enseq_LED3_default(Application* handle)
{
	/* 'default' enter sequence for region LED3 */
	react_LED3__entry_Default(handle);
}

/* 'default' enter sequence for region r1 */
static void enseq_LED3_TITILA_r1_default(Application* handle)
{
	/* 'default' enter sequence for region r1 */
	react_LED3_TITILA_r1__entry_Default(handle);
}

/* Default exit sequence for state DEBOUNCE */
static void exseq_TECX_DEBOUNCE(Application* handle)
{
	/* Default exit sequence for state DEBOUNCE */
	handle->stateConfVector[0] = Application_last_state;
	handle->stateConfVectorPosition = 0;
	exact_TECX_DEBOUNCE(handle);
}

/* Default exit sequence for state NO_OPRIMIDO */
static void exseq_TECX_NO_OPRIMIDO(Application* handle)
{
	/* Default exit sequence for state NO_OPRIMIDO */
	handle->stateConfVector[0] = Application_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state OPRIMIDO */
static void exseq_TECX_OPRIMIDO(Application* handle)
{
	/* Default exit sequence for state OPRIMIDO */
	handle->stateConfVector[0] = Application_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state VALIDACION */
static void exseq_TECX_VALIDACION(Application* handle)
{
	/* Default exit sequence for state VALIDACION */
	handle->stateConfVector[0] = Application_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state ESPERA */
static void exseq_main_region_ESPERA(Application* handle)
{
	/* Default exit sequence for state ESPERA */
	handle->stateConfVector[1] = Application_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for state TITILA */
static void exseq_LED3_TITILA(Application* handle)
{
	/* Default exit sequence for state TITILA */
	exseq_LED3_TITILA_r1(handle);
}

/* Default exit sequence for state ENCENDIDO */
static void exseq_LED3_TITILA_r1_ENCENDIDO(Application* handle)
{
	/* Default exit sequence for state ENCENDIDO */
	handle->stateConfVector[2] = Application_last_state;
	handle->stateConfVectorPosition = 2;
	exact_LED3_TITILA_r1_ENCENDIDO(handle);
}

/* Default exit sequence for state APAGADO */
static void exseq_LED3_TITILA_r1_APAGADO(Application* handle)
{
	/* Default exit sequence for state APAGADO */
	handle->stateConfVector[2] = Application_last_state;
	handle->stateConfVectorPosition = 2;
	exact_LED3_TITILA_r1_APAGADO(handle);
}

/* Default exit sequence for state REPOSO */
static void exseq_LED3_REPOSO(Application* handle)
{
	/* Default exit sequence for state REPOSO */
	handle->stateConfVector[2] = Application_last_state;
	handle->stateConfVectorPosition = 2;
}

/* Default exit sequence for region TECX */
static void exseq_TECX(Application* handle)
{
	/* Default exit sequence for region TECX */
	/* Handle exit of all possible states (of application.TECX) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Application_TECX_DEBOUNCE :
		{
			exseq_TECX_DEBOUNCE(handle);
			break;
		}
		case Application_TECX_NO_OPRIMIDO :
		{
			exseq_TECX_NO_OPRIMIDO(handle);
			break;
		}
		case Application_TECX_OPRIMIDO :
		{
			exseq_TECX_OPRIMIDO(handle);
			break;
		}
		case Application_TECX_VALIDACION :
		{
			exseq_TECX_VALIDACION(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region main region */
static void exseq_main_region(Application* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of application.main_region) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Application_main_region_ESPERA :
		{
			exseq_main_region_ESPERA(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region LED3 */
static void exseq_LED3(Application* handle)
{
	/* Default exit sequence for region LED3 */
	/* Handle exit of all possible states (of application.LED3) at position 2... */
	switch(handle->stateConfVector[ 2 ])
	{
		case Application_LED3_TITILA_r1_ENCENDIDO :
		{
			exseq_LED3_TITILA_r1_ENCENDIDO(handle);
			break;
		}
		case Application_LED3_TITILA_r1_APAGADO :
		{
			exseq_LED3_TITILA_r1_APAGADO(handle);
			break;
		}
		case Application_LED3_REPOSO :
		{
			exseq_LED3_REPOSO(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void exseq_LED3_TITILA_r1(Application* handle)
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of application.LED3.TITILA.r1) at position 2... */
	switch(handle->stateConfVector[ 2 ])
	{
		case Application_LED3_TITILA_r1_ENCENDIDO :
		{
			exseq_LED3_TITILA_r1_ENCENDIDO(handle);
			break;
		}
		case Application_LED3_TITILA_r1_APAGADO :
		{
			exseq_LED3_TITILA_r1_APAGADO(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state DEBOUNCE. */
static void react_TECX_DEBOUNCE(Application* handle)
{
	/* The reactions of state DEBOUNCE. */
	if (check_TECX_DEBOUNCE_tr0_tr0(handle) == bool_true)
	{ 
		effect_TECX_DEBOUNCE_tr0(handle);
	} 
}

/* The reactions of state NO_OPRIMIDO. */
static void react_TECX_NO_OPRIMIDO(Application* handle)
{
	/* The reactions of state NO_OPRIMIDO. */
	if (check_TECX_NO_OPRIMIDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_TECX_NO_OPRIMIDO_tr0(handle);
	} 
}

/* The reactions of state OPRIMIDO. */
static void react_TECX_OPRIMIDO(Application* handle)
{
	/* The reactions of state OPRIMIDO. */
	if (check_TECX_OPRIMIDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_TECX_OPRIMIDO_tr0(handle);
	} 
}

/* The reactions of state VALIDACION. */
static void react_TECX_VALIDACION(Application* handle)
{
	/* The reactions of state VALIDACION. */
	if (check_TECX_VALIDACION_tr0_tr0(handle) == bool_true)
	{ 
		effect_TECX_VALIDACION_tr0(handle);
	}  else
	{
		if (check_TECX_VALIDACION_tr1_tr1(handle) == bool_true)
		{ 
			effect_TECX_VALIDACION_tr1(handle);
		} 
	}
}

/* The reactions of state ESPERA. */
static void react_main_region_ESPERA(Application* handle)
{
	/* The reactions of state ESPERA. */
	if (check_main_region_ESPERA_tr0_tr0(handle) == bool_true)
	{ 
		effect_main_region_ESPERA_tr0(handle);
	}  else
	{
		if (check_main_region_ESPERA_tr1_tr1(handle) == bool_true)
		{ 
			effect_main_region_ESPERA_tr1(handle);
		}  else
		{
			if (check_main_region_ESPERA_tr2_tr2(handle) == bool_true)
			{ 
				effect_main_region_ESPERA_tr2(handle);
			}  else
			{
				if (check_main_region_ESPERA_tr3_tr3(handle) == bool_true)
				{ 
					effect_main_region_ESPERA_tr3(handle);
				} 
			}
		}
	}
}

/* The reactions of state ENCENDIDO. */
static void react_LED3_TITILA_r1_ENCENDIDO(Application* handle)
{
	/* The reactions of state ENCENDIDO. */
	if (check_LED3_TITILA_tr0_tr0(handle) == bool_true)
	{ 
		effect_LED3_TITILA_tr0(handle);
	}  else
	{
		if (check_LED3_TITILA_r1_ENCENDIDO_tr0_tr0(handle) == bool_true)
		{ 
			effect_LED3_TITILA_r1_ENCENDIDO_tr0(handle);
		} 
	}
}

/* The reactions of state APAGADO. */
static void react_LED3_TITILA_r1_APAGADO(Application* handle)
{
	/* The reactions of state APAGADO. */
	if (check_LED3_TITILA_tr0_tr0(handle) == bool_true)
	{ 
		effect_LED3_TITILA_tr0(handle);
	}  else
	{
		if (check_LED3_TITILA_r1_APAGADO_tr0_tr0(handle) == bool_true)
		{ 
			effect_LED3_TITILA_r1_APAGADO_tr0(handle);
		} 
	}
}

/* The reactions of state REPOSO. */
static void react_LED3_REPOSO(Application* handle)
{
	/* The reactions of state REPOSO. */
	if (check_LED3_REPOSO_tr0_tr0(handle) == bool_true)
	{ 
		effect_LED3_REPOSO_tr0(handle);
	} 
}

/* Default react sequence for initial entry  */
static void react_TECX__entry_Default(Application* handle)
{
	/* Default react sequence for initial entry  */
	enseq_TECX_NO_OPRIMIDO_default(handle);
}

/* Default react sequence for initial entry  */
static void react_main_region__entry_Default(Application* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_ESPERA_default(handle);
}

/* Default react sequence for initial entry  */
static void react_LED3_TITILA_r1__entry_Default(Application* handle)
{
	/* Default react sequence for initial entry  */
	enseq_LED3_TITILA_r1_APAGADO_default(handle);
}

/* Default react sequence for initial entry  */
static void react_LED3__entry_Default(Application* handle)
{
	/* Default react sequence for initial entry  */
	enseq_LED3_REPOSO_default(handle);
}


