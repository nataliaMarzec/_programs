
#include "../../botonEnUno/inc/AppModelRENDER.h"

void appModelRender_init(AppModelRender * render, AppModel * model, gpioMap_t gpio){
	render->model2 = model;
	render->gpio2 = gpio;
}

void appModelRender_update(AppModelRender * render) {
	gpioWrite(render->gpio2, appModel_isEnabled(render->model2));
}



