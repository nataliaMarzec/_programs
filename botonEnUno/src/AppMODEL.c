#include "../../botonEnUno/inc/AppMODEL.h"


void appModel_init(AppModel * model, unsigned char enabled) {
	model->enabled = enabled;
}

void setValue(AppModel * model, unsigned char value) {
	model->enabled = value;
}

void appModel_enable(AppModel * model) {
	setValue(model, 1);
}

void appModel_disable(AppModel * model) {
	setValue(model, 0);
}

unsigned char appModel_isEnabled(AppModel * model) {
	return model->enabled;
}

void appModel_toggle(AppModel * model){
	setValue(model, !model->enabled);
}


