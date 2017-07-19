/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   CAppReceiver.cpp
* Author: User
*
* Created on 16 de noviembre de 2016, 16:30
*/


#include "CAppReceiver.h"

CAppReceiver::CAppReceiver() {
	for (int i = 0; i < KEY_KEY_CODES_COUNT; i++) {
		KeyDown[i] = false;
	}

}

bool CAppReceiver::OnEvent(const SEvent& event) {

	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}

	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
		case EMIE_LMOUSE_PRESSED_DOWN:
			MouseState.LeftButtonDown = true;
			break;

		case EMIE_LMOUSE_LEFT_UP:
			MouseState.LeftButtonDown = false;
			break;

		case EMIE_MOUSE_MOVED:
			MouseState.Position.X = event.MouseInput.X;
			MouseState.Position.Y = event.MouseInput.Y;
			break;

		default:
			// We won't use the wheel
			break;
		}
	}

	return false;
}

const CAppReceiver::SMouseState& CAppReceiver::GetMouseState(void) const {
	return MouseState;
}

bool CAppReceiver::isKeyDown(EKEY_CODE keyCode) const {
	return KeyDown[keyCode];
}

bool CAppReceiver::isKeyUp(EKEY_CODE keyCode) const {
	return !KeyDown[keyCode];

}
