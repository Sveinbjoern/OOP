/*
  ==============================================================================

    FileManagment.h
    Created: 14 Mar 2022 2:59:05pm
    Author:  Me

  ==============================================================================
*/

#pragma once

//needs acces to playlist and GUI and juce functions
#include <juceheader.h>
#include "PlaylistComponent.h"
#include "Deck.h"
#include "Track.h"
#include "SoundElement.h"


class FileManagement
{
    PlaylistComponent* playlistComponent;
    Deck* leftDeck;
    Deck* rightDeck;


};
