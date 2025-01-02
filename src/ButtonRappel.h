#pragma once

#ifndef BUTTONRAPPEL_H
#define BUTTONRAPPEL_H

#include <Arduino.h>
#include <OneButton.h>

// Définir le GPIO du bouton Rappel
#define RAPPEL_BUTTON_PIN 19 // Remplacez ce GPIO par celui que vous utilisez

class ButtonRappel {
  public:
    ButtonRappel();
    void setup();
    void tick();

  private:
    OneButton rappelButton;

    // Méthodes statiques pour gérer les événements du bouton
    static void onClick();
    static void onDoubleClick();
    static void onLongPressStart();
    static void onLongPressStop();
};

#endif // BUTTONRAPPEL_H



