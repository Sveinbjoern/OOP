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
PlaylistComponent::PlaylistComponent(juce::Button::Listener* _ButtonListener) : mainComponentButtonListener(_ButtonListener)
{


	std::ifstream infile{ "playlist.cfg" };
	if (infile.is_open())
	{
		infile >> currentPlaylistFile;
		DBG("PlaylistComponent::PlaylistComponent currentPlaylistFile : " << currentPlaylistFile);
		infile.close();

	}
	else
	{
		std::ofstream outfile{ "playlist.cfg" };
		std::string playlist;
		outfile << "playlist.pl\n";
		outfile << "configfile containing saved playlist file name";
		outfile.close();
	}

	auto& header = tableListBox.getHeader();
	header.addColumn("", 1, 32);
	header.addColumn("Track name", 2, 200);
	header.addColumn("Track Length", 3, 200);
	header.addColumn("Full Path", 4, 200);
	header.addColumn("", 5, 32);
	header.addColumn("", 6, 25);

	tableListBox.setModel(this);

	addAndMakeVisible(tableListBox);



	loadPlaylist();

	setSearchedTracksToDefault();
	
	if (checkValidPlaylist())
		DBG("PlaylistComponent::PlaylistComponent track is valid ");
	else
		DBG("PlaylistComponent::PlaylistComponent track is not valid ");

	tableListBoxUpdate();
	//tableListBox.selectRow(2);



}

PlaylistComponent::~PlaylistComponent()
{
	for (int i = 0; i < tracks.size(); ++i)
	{
		delete tracks[i];
	}
}

void PlaylistComponent::paint(juce::Graphics& g)
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
	header.setColumnWidth(4, widthWithoutButtons - header.getColumnWidth(2) - header.getColumnWidth(3));

	//tableListBox.setRowHeight(getHeight()/10);
}


bool PlaylistComponent::addToSetOfTracks(const juce::File& audioFile)
{
	std::pair<std::set<juce::String>::iterator, bool> ret = setOfTracks.insert(audioFile.getFullPathName());

	return ret.second;//ret.second is true if it was a new Track   
}


void PlaylistComponent::tableListBoxUpdate()
{

	tableListBox.updateContent();
}

void PlaylistComponent::addTrack(Track* track)
{

	//Track track{ audioFile };
	//DBG("PlaylistComponet::addtrack " << tracks.size());
	if (tracks.size() == 0)
	{
		tracks.push_back(track);
	}
	else
	{
		juce::String fullPath = track->fullPath;
		int start = 0;
		int end = tracks.size() - 1;
		int current = end / 2;
		int index = binarySearchInsertLocation(start, end, current, fullPath);
		std::vector<Track*>::iterator it;
		it = tracks.begin() + index;
		tracks.insert(tracks.begin() + index, track);
		

	}

	setSearchedTracksToDefault();

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
	DBG("PlaylistComponent::binarySearch START start end current " << start << " " << end << " " << current);
	int compareInt = tracks[current]->fullPath.compare(fullPath);
	DBG("PlaylistComponent::binarySearch compareInt " << compareInt);
	if (compareInt == 0) return current;
	if (start >= end || current == 0)
	{
		//DBG("PlaylistComponent::binarySearch start==end");
		//if (compareInt < 0) //tracks[current] comes before fullPath
		//{
		//	//DBG("PlaylistComponent::binarySearch compareInt <0");
		//	return current;
		//}
		//else // fullPath comes before tracks[current]
		//{
		//	// DBG("PlaylistComponent::binarySearch compareInt >0");
		//	return current + 1;
		//}
		return -1;

	}

	if (compareInt < 0) //tracks[current] comes before fullPath
	{
		start = current + 1;
		current = (start + end) / 2;
		//DBG("PlaylistComponent::binarySearch compareInt < 0");
		//DBG("PlaylistComponent::binarySearch start , end , current: " << start << " "<< end<< " "<< current);
		binarySearch(start, end, current, fullPath);

	}
	else // fullPath comes before tracks[current]
	{
		end = current - 1;
		current = (start + end) / 2;
		//DBG("PlaylistComponent::binarySearch compareInt > 0");
		//DBG("PlaylistComponent::binarySearch start , end , current: " << start << " " << end << " " << current);
		binarySearch(start, end, current, fullPath);
	}
}

int PlaylistComponent::binarySearchInsertLocation(int& start, int& end, int& current, juce::String& fullPath)
{
	DBG("PlaylistComponent::binarySearch START start end current " << start << " " << end << " " << current);
	DBG("PlaylistComponent::binarySearch fullPath " << fullPath);
	DBG("PlaylistComponent::binarySearch tracks[current]->fullPath" << tracks[current]->fullPath);
	int compareInt = tracks[current]->fullPath.compare(fullPath);
	DBG("PlaylistComponent::binarySearch compareInt " << compareInt);
	if (compareInt == 0) { DBG("PlaylistComponent::binarySearchInsertLocation duplicate item"); return -1; }
	if (start >= end || current == 0)
	{
		DBG("PlaylistComponent::binarySearch start==end || current == 0" );
		if (compareInt > 0) //tracks[current] comes before fullPath
		{
			DBG("PlaylistComponent::binarySearch compareInt <0 " << current);
			return current;
		}
		else // fullPath comes before tracks[current]
		{
			DBG("PlaylistComponent::binarySearch compareInt >0 " << current+1);
			return current + 1;
		}

	}

	if (compareInt < 0) //tracks[current] comes before fullPath
	{
		start = current + 1;
		current = (start + end) / 2;
		DBG("PlaylistComponent::binarySearch compareInt < 0");
		DBG("PlaylistComponent::binarySearch start , end , current: " << start << " "<< end<< " "<< current);
		binarySearchInsertLocation(start, end, current, fullPath);

	}
	else // fullPath comes before tracks[current]
	{
		end = current - 1;
		current = (start + end) / 2;
		DBG("PlaylistComponent::binarySearch compareInt > 0");
		DBG("PlaylistComponent::binarySearch start , end , current: " << start << " " << end << " " << current);
		binarySearchInsertLocation(start, end, current, fullPath);
	}
}


Track* PlaylistComponent::getTrack(juce::File& audioFile)
{
	juce::String fullPath = audioFile.getFullPathName();
	DBG("PlaylistComponent::getTrack fullPath " << audioFile.getFullPathName());


	int start = 0;
	int end = tracks.size() - 1;
	int current = end / 2;
	int index = binarySearch(start, end, current, fullPath);

	return tracks[index];
}

bool PlaylistComponent::checkValidPlaylist()
{
	if (tracks.size() <= 1)
		return true;
	for (int i = 0; i < tracks.size() - 1; ++i)
	{
		DBG("PLaylistComponent::checkValidPlaylist checking");
		if (tracks[i]->fullPath.compare(tracks[i + 1]->fullPath) > 0)
			return false;
		DBG("PLaylistComponent::checkValidPlaylist true " << i);
	}
	return true;
}

int PlaylistComponent::getTrackIndex(const juce::File& audioFile)
{
	juce::String fullPath = audioFile.getFullPathName();
	DBG("PlaylistComponent::getTrack fullPath " << audioFile.getFullPathName());

	int start = 0;
	int end = tracks.size() - 1;
	int current = end / 2;
	int index = binarySearch(start, end, current, fullPath);

	return index;
}

Track* PlaylistComponent::getTrack(int index)
{
	if (index >= 0 && index < tracks.size())
		return tracks[index];
	DBG("PlaylistComponent::getTrack " << index << " is out of tracks range.");
	return nullptr;
}

void PlaylistComponent::setSearchedTracksToDefault()
{
	searchedTracks = tracks;
}

void PlaylistComponent::setSearchedTracks(juce::String& searchTerm)
{
	DBG("PlaylistComponent::setSearchedTracks serachTerm is not empty");
	searchedTracks.clear();

	for (int i = 0; i < tracks.size(); ++i)
	{
		//DBG("PlaylistComponent::setSearchedTracks serachTerm while loop running");
		if (tracks[i]->getFileName().contains(searchTerm))
		{
			searchedTracks.push_back(tracks[i]);
			DBG("PlaylistComponent::setSearchedTracks serachTerm is found at tracks index " << i);
		}
		//track = getTrack(++i);
	}
	tableListBoxUpdate();

	DBG("PlaylistComponent::setSearchedTracks all tracks in searchedTracks");
}

std::vector<Track*>& PlaylistComponent::getSearchedTracks()
{
	return searchedTracks;
}

void PlaylistComponent::deleteTrack(int index)
{
	//Check valid input   
	if (index < 0 || index > searchedTracks.size() - 1)
	{
		DBG("PlaylistComponent::deleteTrack index " << index << " is out of range.");
		return;
	}
	if (checkValidPlaylist())
		DBG("PlaylistComponent::deleteTrack track is valid ");
	else
		DBG("PlaylistComponent::deleteTrack track is not valid ");

	Track* track = searchedTracks[index];
	setOfTracks.erase(track->fullPath);
	removeFromPlaylist(tracks[index]->fullPath);

	//remove track from tracks, first deleting the pointer
	int indexInTracks = getTrackIndex(track->getAudioFile());
	delete searchedTracks[index];
	tracks.erase(tracks.begin() + indexInTracks);
	//delete searchedTracks[index];
	searchedTracks.erase(searchedTracks.begin() + index);

	for (int i = tracks.size()-1; i >=0  ; --i)
	{
			DBG(i << " all tracks in tracks " << tracks[i]->fullPath);
	}
	
	for (int i = 0; i < searchedTracks.size(); ++i)
	{
		DBG(i << " all tracks in searchedTracks " << searchedTracks[i]->fullPath);
	}
	tableListBoxUpdate();
}

//================================================================================================
//Functions from juce::TableListBoxModel
int PlaylistComponent::getNumRows()
{
	return searchedTracks.size();
	//return tracks.size();
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
		if (rowNumber % 2)
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
	if (rowNumber >= searchedTracks.size())
		return;


	switch (columnId)
	{
	case 1:
		return;
	case 2:
		g.drawText(searchedTracks[rowNumber]->getFileName(), 2, 0, width - 4, height, juce::Justification::centredLeft, true);
		//g.setColour(juce::Colours::grey);
		g.drawRect(0,0,width,height, 1);
		break;
	case 3:
		//DBG("PLaylistComponent::PaintCell getTrackLenghtString"<<tracks[rowNumber].getTrackLengthString().toStdString());
		//DBG("PLaylistComponent::PaintCell getFileName" << tracks[rowNumber].getFileName().toStdString());
		//DBG("PLaylistComponent::PaintCell fullPath" << tracks[rowNumber].fullPath.toStdString());
		g.drawText(searchedTracks[rowNumber]->getTrackLengthString(), 2, 0, width - 4, height, juce::Justification::centredLeft, true);
		//g.setColour(juce::Colours::grey);
		//g.drawRect(getLocalBounds(), 1);
		g.drawRect(0, 0, width, height, 1);
		break;
	case 4:
		g.drawText(searchedTracks[rowNumber]->fullPath, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
		//g.setColour(juce::Colours::grey);
		//g.drawRect(getLocalBounds(), 1);
		g.drawRect(0, 0, width, height, 1);
		break;
	case 5:
		return;
	case 6:
		return;

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
			button->setComponentID(juce::String(rowNumber * 10 + columnId));
			(columnId == 1 ? button->setColour(juce::TextButton::buttonColourId, juce::Colours::blue) : button->setColour(juce::TextButton::buttonColourId, juce::Colours::red));

			exisitingComponentToUpdate = button;
		}
	}
	else if (columnId == 6)
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
void PlaylistComponent::saveToPlaylist(Track* track)
{


	try
	{
		//std::ofstream outfile{ "playlist.pl", std::ofstream::binary };
		std::ofstream outfile{ currentPlaylistFile, std::ofstream::binary | std::ofstream::app };
		//std::string str("whatever");

		if (!outfile.is_open())
		{
			DBG("PlaylistComponent::removeFromPlaylist could not read from playlist.pl");
			return;
		}


		//DBG("PlaylistComponent::savePlaylist str " << str);
		size_t size = track->fullPath.length();
		//DBG("PlaylistComponent::savePlaylist size " << size);
		//outfile.write(&size, sizeof(size));
		outfile.write((char*)&size, sizeof(size));
		outfile.write(&track->fullPath.toStdString()[0], size);
		juce::String trackLengthString = track->getTrackLengthString();
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
		std::ifstream infile{ currentPlaylistFile, std::ifstream::binary };
		if (!infile.is_open())
		{
			DBG("PlaylistComponent::loadPlaylist could not read from playlist.pl");
			return;
		}

		std::string str;
		size_t size;
		while (infile.read((char*)&size, sizeof(size)))
		{
			//DBG("PlaylistComponent::loadPlaylist size " << size);
			str.resize(size);
			infile.read(&str[0], size);
			//DBG("PlaylistComponent::loadPlaylist file content " << str);

			juce::String fullPath{ str };
			infile.read((char*)&size, sizeof(size));
			str.resize(size);
			infile.read(&str[0], size);
			//put track into setOfTracks
			if (addToSetOfTracks(fullPath))
			{

				Track* track = new Track{ fullPath };

				juce::String trackLengthString{ str };
				juce::String stringToAdd{ "/" };
				stringToAdd.append(trackLengthString, 10);
				stringToAdd.append(" s", 2);

				track->setValuesAfterFirstLoad(trackLengthString, stringToAdd);
				//DBG("Deck::addNewTrack newTrack.fullPath" << track->fullPath);
				//DBG("Deck::addNewTrack getTrackLengthString" << track->getTrackLengthString());
				addTrack(track);

				DBG("PlaylistComponent::loadPlaylist tracks.size() " << tracks.size());
				for (int i = 0; i < tracks.size(); ++i)
				{
					DBG(i << " PlaylistComponent::loadPlaylist all elments in tracks " << tracks[i]->fullPath);
				}
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

// Made with help from: https://www.geeksforgeeks.org/set-position-with-seekg-in-cpp-language-file-handling/
void PlaylistComponent::removeFromPlaylist(const juce::String fullPath)
{
	//try {
		std::ifstream infile{ currentPlaylistFile, std::ifstream::binary };
		if (!infile.is_open())
		{
			DBG("PlaylistComponent::removeFromPlaylist could not read from " << currentPlaylistFile << "!");
			return;
		}

		//std::ostringstream in_memory_stream;
		std::ofstream newList("temp.tmp", std::ios::out | std::ios::binary);


		std::string str;
		size_t size;


		bool found = false;
		while (!found && infile.read((char*)&size, sizeof(size)) )
		{
			//Only if the string is of the right size needs to be checked
			if (size != fullPath.length())
			{
				str.resize(size);
				infile.read(&str[0], size);
				//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete size " << size);
				//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete str " << str);
				newList.write((char*)&size, sizeof(size));
				newList.write(&str[0], size);

				infile.read((char*)&size, sizeof(size));
				str.resize(size);
				infile.read(&str[0], size); 
				//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete size " << size);
				//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete str " << str);
				newList.write((char*)&size, sizeof(size));
				newList.write(&str[0], size);
			}
			else
			{
				
				str.resize(size);
				infile.read(&str[0], size);
				if (str != fullPath.toStdString())
				{
					//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete size " << size);
					//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete str " << str);
					newList.write((char*)&size, sizeof(size));
					newList.write(&str[0], size);
					//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete size " << size);
					//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete str " << str);
					infile.read((char*)&size, sizeof(size));
					str.resize(size);
					infile.read(&str[0], size);

					newList.write((char*)&size, sizeof(size));
					newList.write(&str[0], size);
					//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete size " << size);
					//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete str " << str);
					

				}
				else
				{
					
					
					
					//DBG("PlaylistComponent::removeFromPlaylist File to delete size " << size);
					//DBG("PlaylistComponent::removeFromPlaylist File to delete str " << str);

					infile.read((char*)&size, sizeof(size));
					//str.resize(size);
					//infile.read(&str[0], size);
					infile.seekg(size, std::ios::cur);
					
					//DBG("PlaylistComponent::removeFromPlaylist File to delete size " << size);
					//DBG("PlaylistComponent::removeFromPlaylist File to delete str " << str);
					found = true;

				}

			}


		}
		while (infile.read((char*)&size, sizeof(size)))
		{
			str.resize(size);
			infile.read(&str[0], size);
			//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete size " << size);
			//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete str " << str);
			newList.write((char*)&size, sizeof(size));
			newList.write(&str[0], size);

			infile.read((char*)&size, sizeof(size));
			str.resize(size);
			infile.read(&str[0], size);
			//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete size " << size);
			//DBG("PlaylistComponent::removeFromPlaylist Not an file to delete str " << str);
			newList.write((char*)&size, sizeof(size));
			newList.write(&str[0], size);

		}
		//DBG("PlaylistComponent::loadPlaylist file content " << str);

		if (!found)
		{
			DBG("PlaylistComponent::removeFromPlaylist file not found in playlist");
		}
		infile.close();
		newList.close();
		//std::ofstream outfile{ currentPlaylistFile, std::ofstream::binary };
		//outfile << newList.rdbuf();
		if (std::remove(currentPlaylistFile.c_str()) == 0)
			DBG("PlaylistComponent::removeFromPlaylist Delete file worked");
		else
			DBG("PlaylistComponent::removeFromPlaylist Delete file failed");
		//rename("temp.tmp", currentPlaylistFile);
		if (rename("temp.tmp", currentPlaylistFile.c_str()) == 0)
			DBG("PlaylistComponent::removeFromPlaylist Rename file worked");
		else
			DBG("PlaylistComponent::removeFromPlaylist Rename file failed");
		
	//}
	//catch (const std::exception& e)
	//{
	//	DBG(e.what());
	//	//return false;
	//};
}
