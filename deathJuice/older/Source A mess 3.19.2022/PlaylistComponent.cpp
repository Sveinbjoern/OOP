/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 9 Mar 2022 4:03:40pm
    Author:  Angie Carola

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
//#include "Track.h"


//==============================================================================
PlaylistComponent::PlaylistComponent(juce::Button::Listener* _ButtonListener): mainComponentButtonListener(_ButtonListener)
{
    auto& header = tableListBox.getHeader();
    header.addColumn("", 1, 32);
    header.addColumn("Track name" , 2, 200);
    header.addColumn("Track Length", 3, 200);
    header.addColumn("Full Path", 4, 200);
    header.addColumn("", 5, 32);
    header.addColumn("", 6, 25);

    tableListBox.setModel(this);

    addAndMakeVisible(tableListBox);

    
    loadPlaylist();
    //tracks[0] = tracks[0];
    //Track tempTrack = *tracks[1];
    
    DBG("PlaylistComponent::PlaylistComponent tempTrack " << tracks[0]->fullPath);
    //tracks[0] = tracks[3];
    //if (tracks[0] == tracks[3])
    //    DBG("PlaylistComponent::PlaylistComponent tracks[0]== tracks[3] true");
    //else
    //    DBG("PlaylistComponent::PlaylistComponent tracks[0]== tracks[3] false");
    //
    //if (tracks[3] == tracks[3])
    //    DBG("PlaylistComponent::PlaylistComponent tracks[3]== tracks[3] true");
    //else
    //    DBG("PlaylistComponent::PlaylistComponent tracks[3]== tracks[3] false");
    //
    //DBG("PlaylistComponent::PlaylistComponent tracks[0] after " << tracks[0]->fullPath);
    //tracks[3] = &tempTrack;
    //tableListBoxUpdate();

}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    //
    //g.setColour (juce::Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    //
    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("PlaylistComponent", getLocalBounds(),
    //            juce::Justification::centred, true);   // draw some placeholder text


}

void PlaylistComponent::resized()
{
    juce::TableHeaderComponent& header = tableListBox.getHeader();
    
    int sumOfButtonWidths = header.getColumnWidth(1) + header.getColumnWidth(5) + header.getColumnWidth(6);
    tableListBox.setBounds(getLocalBounds());
    int widthWithoutButtons = getWidth() - sumOfButtonWidths;
    int columnWidth = widthWithoutButtons / 6;
    header.setColumnWidth(2, columnWidth);
    header.setColumnWidth(3, columnWidth);
    header.setColumnWidth(4, widthWithoutButtons -  header.getColumnWidth(2) - header.getColumnWidth(3));
    
}


bool PlaylistComponent::addToSetOfTracks(const juce::File& audioFile)
{
    std::pair<std::set<juce::String>::iterator ,bool> ret = setOfTracks.insert(audioFile.getFullPathName());
    
    return ret.second;//ret.second is true if it was a new Track
     
                    
}


void PlaylistComponent::tableListBoxUpdate()
{
    
    tableListBox.updateContent();
}

Track& PlaylistComponent::addTrack( Track* track)
{
    
    //Track track{ audioFile };
    DBG("PlaylistComponet::addtrack " << tracks.size());
    if (tracks.size() == 0)
    {
        tracks.push_back(track);
    }
    else
    {
        juce::String fullPath = track->fullPath;
        int start = 0;
        int end = tracks.size()-1;
        int current = end / 2;
        int index = binarySearch(start, end, current, fullPath);
        std::vector<Track*>::iterator it;
        it = tracks.begin()+index;
        tracks.insert(tracks.begin() + index,track);
    }


    

    //DBG("This should not run");
    
    //ints.insert(ints.begin() +index, 5 );
    //tracks.insert(tracks.begin(), Track(audioFile));
    
    DBG("PlaylistComponet::addtrack tracks after insert " << tracks.size());
    
    return *track;
    


}

void PlaylistComponent::addTracks(const juce::StringArray& s)
{
    

}

/**Binary search of the tracks 
This will return the index of a track that is in the vector or the place to insert an new element if it
is not in the vector.

juce::File::compare returns 0 if the two strings are identical; 
negative if this string comes before the other one alphabetically, or positive if it comes after it.

Takes a full path of a valid sound file in the form off a juce::String.
*/
int PlaylistComponent::binarySearch(int& start, int& end, int& current, juce::String& fullPath)
{
    //DBG("PlaylistComponent::binarySearch START start end current " << start << " " << end << " " << current);
    int compareInt = tracks[current]->fullPath.compare(fullPath);
    //DBG("PlaylistComponent::binarySearch compareInt " << compareInt);
    if (compareInt == 0) return current;
    if (start == end || current == 0)
    {
        //DBG("PlaylistComponent::binarySearch start==end");
        if (compareInt < 0) //tracks[current] comes before fullPath
        {
            //DBG("PlaylistComponent::binarySearch compareInt <0");
            return current;
        }
        else // fullPath comes before tracks[current]
        {
           // DBG("PlaylistComponent::binarySearch compareInt >0");
            return current + 1;
        }

    }

    if (compareInt < 0) //tracks[current] comes before fullPath
    {
        start = current + 1;
        current = ( current + end) / 2;
        //DBG("PlaylistComponent::binarySearch compareInt < 0");
        //DBG("PlaylistComponent::binarySearch start , end , current: " << start << " "<< end<< " "<< current);
        binarySearch(start, end , current, fullPath );

    }
    else // fullPath comes before tracks[current]
    {
        end = current - 1;
        current = (start + current) / 2;
        //DBG("PlaylistComponent::binarySearch compareInt > 0");
        //DBG("PlaylistComponent::binarySearch start , end , current: " << start << " " << end << " " << current);
        binarySearch( start , end, current, fullPath);
    }
}
Track& PlaylistComponent::getTrack( juce::File& audioFile)
{
    juce::String fullPath = audioFile.getFullPathName();
    DBG("PlaylistComponent::getTrack fullPath "<< audioFile.getFullPathName());
   

    int start = 0;
    int end = tracks.size()-1;
    int current = end / 2;
    int index = binarySearch(start, end, current, fullPath);

    return *tracks[index];
}

Track& PlaylistComponent::getTrack(int index)
{
    if (index >= 0 && index < tracks.size())
        return *tracks[index];
    DBG("PlaylistComponent::getTrack " << index << " is out of tracks range.");
        
}

void PlaylistComponent::deleteTrack(int index)
{
    //Check valid input   
    if (index < 0 || index > tracks.size()-1)
    {
        DBG("PlaylistComponent::deleteTrack index " << index << " is out of range.");
        return;
    }   
        
    //auto cell = tableListBox.getCellComponent(3, index);
    //juce::String s{};
    //cell->getChildren().contains(s);
    
    //find fullpath and remove from setOfTracks
    Track& track = *tracks[index];
    DBG("PlaylistComponent::deleteTrack track.fullpath" << track.fullPath);
    
        DBG("PlaylistComponent::deleteTrack index " << index);
        //DBG("PlaylistComponent::deleteTrack setOfTRack size before " << setOfTracks.size());
        setOfTracks.erase(track.fullPath);


        //for (int i = 0; i < tracks.size(); ++i)
        //{
        //    DBG(i << " all tracks in tracks " << tracks[i].fullPath);
        //}
        //DBG("PlaylistComponent::deleteTrack setOfTRack size after " << setOfTracks.size());
        
        //DBG("PlaylistComponent::deleteTrack tracks size befoer " << tracks.size());
        
        //juce::String fullPath = track.fullPath;
        //int start = 0;
        //int end = tracks.size() - 1;
        //int current = end / 2;
        //int i = binarySearch(start, end, current, fullPath);
        //
        //DBG("PlaylistComponent::deleteTrack i " << i);
        //DBG("PlaylistComponent::deleteTrack index " << index);
        //DBG("PlaylistComponent::deleteTrack tracks.begin() " << track.begin());
        //auto bab = tracks.begin();
        //Track& bab = tracks.begin();


       // DBG("PlaylistComponent::deleteTrack track at index " << bab->fullPath);
        

        //remove track from tracks 
        //std::vector<Track> copy;
        //
        //for (int i = 0; i < tracks.size(); ++i)
        //{
        //    if (i != index)
        //        copy.push_back(tracks[i]);
        //
        //}
        ////tracks.pop_back();
        //
        //for (int i = 0; i < copy.size(); ++i)
        //{
        //    //tracks[i] = copy[i];
        //    DBG(i << " all tracks in copy " << copy[i].fullPath);
        //
        //}
        
        
        tracks.erase(tracks.begin()+index);

        for (int i = 0; i < tracks.size(); ++i)
        {
            DBG(i << " all tracks in tracks " << tracks[i]->fullPath);
        }
        //DBG("PlaylistComponent::deleteTrack i " << i);
        //tracks.erase(tracks.begin() + i);
        DBG("PlaylistComponent::deleteTrack tracks size after " << tracks.size());
        tableListBoxUpdate();

    
}

//================================================================================================
//Functions from juce::TableListBoxModel
int PlaylistComponent::getNumRows()
{
    return tracks.size();
}
void PlaylistComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    //DBG("PlaylistComponet::paintRowBackground");
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::darkseagreen);
    }
    else
    {
        if (rowNumber%2)  
        {
            g.fillAll(juce::Colours::darkgrey);
        }
        else  g.fillAll(juce::Colours::grey);

    }

}
void PlaylistComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    //DBG("PlaylistComponent::paintCell rowNumber" << rowNumber);
    
    //Guard against invalid numbers
    if (rowNumber >= tracks.size())
        return;


    switch (columnId)
    {
    case 1:
        return;
    case 2:
        g.drawText(tracks[rowNumber]->getFileName(), 2, 0, width - 4, height, juce::Justification::centredLeft, true);
        //g.setColour(juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);
        break;
    case 3:
        //DBG("PLaylistComponent::PaintCell getTrackLenghtString"<<tracks[rowNumber].getTrackLengthString().toStdString());
        //DBG("PLaylistComponent::PaintCell getFileName" << tracks[rowNumber].getFileName().toStdString());
        //DBG("PLaylistComponent::PaintCell fullPath" << tracks[rowNumber].fullPath.toStdString());
        g.drawText( tracks[rowNumber]->getTrackLengthString(), 2, 0, width - 4, height, juce::Justification::centredLeft, true);
        //g.setColour(juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);
        break;
    case 4:
        g.drawText(tracks[rowNumber]->fullPath, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
        //g.setColour(juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);
        break;
    case 5:
        return;
    case 6:
        break;

    default:
        DBG("Invalid columNumber given to PlaylistComponent::paintCell");
        break;
    }

    

}

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelcted, juce::Component* exisitingComponentToUpdate)
{
    //DBG("PlaylistComponet::refreshComponentForCell");
    if (columnId == 1 || columnId == 5)
    {
        if (exisitingComponentToUpdate == nullptr)
        {
            juce::TextButton* button = new juce::TextButton("ADD");

            button->addListener(mainComponentButtonListener);
            button->setComponentID(juce::String( rowNumber * 10 + columnId));
            (columnId == 1 ? button->setColour(juce::TextButton::buttonColourId,juce::Colours::blue) : button->setColour(juce::TextButton::buttonColourId,juce::Colours::red));
            
            exisitingComponentToUpdate = button;
        }
    }
    else if(columnId == 6)
    {
        if (exisitingComponentToUpdate == nullptr)
        {
            juce::TextButton* button = new juce::TextButton("X");
            button->addListener(mainComponentButtonListener);
            button->setComponentID(juce::String(rowNumber * 10 + columnId));

            exisitingComponentToUpdate = button;
        }

    }
    return exisitingComponentToUpdate;
}

//void PlaylistComponent::callRepaint()
//{
//    repaint();
//}

//================================================================================================
//Event handling functions
void PlaylistComponent::buttonClicked(juce::Button* button)
{
  
    
}

//================================================================================================
// storage managment functions



//Adapted from: https://stackoverflow.com/questions/10873382/write-and-read-string-to-binary-file-c
void PlaylistComponent::saveToPlaylist(Track& track)
{
    
    
    try
    {
        //std::ofstream outfile{ "playlist.pl", std::ofstream::binary };
        std::ofstream outfile{ "playlist.pl", std::ofstream::binary | std::ofstream::app };
        //std::string str("whatever");

        

        //DBG("PlaylistComponent::savePlaylist str " << str);
        size_t size = track.fullPath.length();
        //DBG("PlaylistComponent::savePlaylist size " << size);
        //outfile.write(&size, sizeof(size));
        outfile.write((char*)&size, sizeof(size));
        outfile.write(&track.fullPath.toStdString()[0], size);
        juce::String trackLengthString = track.getTrackLengthString();
        size = trackLengthString.length();
        outfile.write((char*)&size, sizeof(size));
        outfile.write(&trackLengthString.toStdString()[0], size);
        

        outfile.close();
        //return true;

    }
 
    
 catch (const std::exception& e)
    {
        DBG(e.what());
        //return false;
    };


   
    

    
}

//Adapted from: https://stackoverflow.com/questions/10873382/write-and-read-string-to-binary-file-c
void PlaylistComponent::loadPlaylist()
{
    



    try {
        std::ifstream infile{ "playlist.pl", std::ifstream::binary };
        std::string str;
        size_t size;
        while (infile.read((char*)&size, sizeof(size)))
        {
            DBG("PlaylistComponent::loadPlaylist size " << size);
            str.resize(size);
            infile.read(&str[0], size);
            DBG("PlaylistComponent::loadPlaylist file content " << str);

            juce::String fullPath{str};
            infile.read((char*)&size, sizeof(size));
            str.resize(size);
            infile.read(&str[0], size);
            //put track into setOfTracks
            if (addToSetOfTracks(fullPath))
            {
                
                Track* track =  &Track{ fullPath };
              
                juce::String trackLengthString{ str };
                juce::String stringToAdd{ "/" };
                stringToAdd.append(trackLengthString, 10);
                stringToAdd.append(" s", 2);

                track->setValuesAfterFirstLoad(trackLengthString, stringToAdd);
                DBG("Deck::addNewTrack newTrack.fullPath" << track->fullPath);
                DBG("Deck::addNewTrack getTrackLengthString" << track->getTrackLengthString());
                addTrack(track);
            }
            //create track
            //Set extra values in track


        }
        infile.close();
    }
    catch (const std::exception& e)
    {
        DBG(e.what());
        //return false;
    };
}