#include "ButtonRappel.h"
#include "MeshService.h" // Pour utiliser la classe MeshService

extern MeshService *service; // Accès à l'instance globale de MeshService

// Constructeur
ButtonRappel::ButtonRappel() : rappelButton(RAPPEL_BUTTON_PIN, true, true) {}

// Configuration du bouton Rappel
void ButtonRappel::setup() {
    rappelButton.attachClick(onClick);
    rappelButton.attachDoubleClick(onDoubleClick);
    rappelButton.attachLongPressStart(onLongPressStart);
    rappelButton.attachLongPressStop(onLongPressStop);
}

// Appelé dans la boucle principale
void ButtonRappel::tick() {
    rappelButton.tick(); // Vérifie l'état du bouton
}

// Gestion du clic simple
void ButtonRappel::onClick() {
    Serial.println("Bouton Rappel : Clic simple détecté !");
    if (service) {
        // Créer un paquet
        meshtastic_MeshPacket packet = meshtastic_MeshPacket_init_default;

        // Remplir les données du paquet
        const char *message = "Rappel";
        size_t messageLength = strlen(message);
        
        if (messageLength < sizeof(packet.decoded.payload.bytes)) { // Utiliser `bytes` pour la copie
            memcpy(packet.decoded.payload.bytes, message, messageLength); // Copie des données
            packet.decoded.payload.bytes[messageLength] = '\0'; // Ajouter le caractère null
            packet.decoded.portnum = meshtastic_PortNum_TEXT_MESSAGE_APP; // Port pour les messages texte

            // Envoyer le paquet via MeshService
            service->sendToMesh(&packet, RX_SRC_LOCAL);
            Serial.println("Message envoyé dans le réseau Mesh !");
        } else {
            Serial.println("Erreur : Message trop long pour le champ payload !");
        }
    }
}

// Gestion du double clic
void ButtonRappel::onDoubleClick() {
    Serial.println("Bouton Rappel : Double clic détecté !");
}

// Gestion du début d'une longue pression
void ButtonRappel::onLongPressStart() {
    Serial.println("Bouton Rappel : Début d'une longue pression détectée !");
}

// Gestion de la fin d'une longue pression
void ButtonRappel::onLongPressStop() {
    Serial.println("Bouton Rappel : Fin d'une longue pression détectée !");
}

