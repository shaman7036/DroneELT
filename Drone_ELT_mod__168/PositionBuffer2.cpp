/*
 * PositionBuffer.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: maciek
 */

/*i don't know why but there are problems with these files, sometimes the serial port doesn't work is some PositionBuffer's are missing.
 * Moved to PositionBuffer2, but PositionBuffer must remain
 */

#include "PositionBuffer2.h"



#include <Arduino.h>
//#include "TinyGPS2.h"
//#include "Utils.h"
#include "MemoryFree.h"


void Position2::update(Position2 position) {
	if(true){
	//if (position.numOfSats >= 3) {
		latitude += position.latitude;
		longitude += position.longitude;
		numOfSats += position.numOfSats;
		hdop += position.hdop;
		numOfSamples++;
	}
}

void Position2::writeStatToSerial() {
	//printDouble( 1.2925254, 5);
	Serial.print("lat=");
	//printDouble(latitude, 5);
	Serial.print(latitude,5);
	Serial.print(" long=");
	Serial.print(longitude,5);
	Serial.print(" ns=");
	//Serial.print(numOfSats, DEC);
	Serial.print(numOfSats);
	Serial.print(" hdop=");
	Serial.println(hdop,2);
	//Serial.print(numOfSamples);

	//Serial.write('p');
	//Serial.write(numOfSats);
	//Serial.write('\n');
	//Serial.flush();
}

void Position2::computeAverage() {
	latitude = latitude / numOfSamples;
	longitude = longitude / numOfSamples;
}


PositionBuffer::PositionBuffer() {
	oneSecondTimer = millis();
	writePos = 0;
}

#if 0

int PositionBuffer::nextForward(int arg) {
	if (arg == BUFFERSIZE)
		return 0;
	return arg + 1;
}

int PositionBuffer::nextBackward(int arg) {
	if (arg == 0)
		return BUFFERSIZE;
	return arg - 1;
}

int PositionBuffer::nextForward(int arg, int offset) {
	int o = arg;
	for (int i = 0; i < offset; i++)
		o = nextForward(o);
	return o;
}

int PositionBuffer::nextBackward(int arg, int offset) {
	int o = arg;
	for (int i = 0; i < offset; i++)
		o = nextBackward(o);
	return o;
}
#endif

void PositionBuffer::addGPSPositionToOneSecondBuffers(Position2 position) {

	if (positionsInCurrentSecond.size() > NUM_OF_SAMPLES_IN_BUFFER)
		positionsInCurrentSecond.remove(0);
	positionsInCurrentSecond.add(0, position);
	//positions[writePos] = position;
	//writePos = nextForward(writePos);
}

void PositionBuffer::updateCurrentSecondPosition(Position2 position) {
	currentSecondPosition.update(position);
}

#if 0
Position2 PositionBuffer::averageFromRange(int previousBegin, int previousEnd) {
	double latitudeAvg = 0.0;
	double longitudeAvg = 0.0;

	int readPos = nextBackward(writePos, previousEnd);
	for (int i = 0; i < (previousBegin - previousEnd + 1); i++) {
		latitudeAvg += positions[readPos].getLatitude();
		longitudeAvg += positions[readPos].getLongitude();
		readPos = nextBackward(readPos);
	}

	latitudeAvg = latitudeAvg / (double) (previousBegin - previousEnd + 1);
	longitudeAvg = longitudeAvg / (double) (previousBegin - previousEnd + 1);
	Position2 result(latitudeAvg, longitudeAvg);
	return result;

}
#endif

#if 0
Position2 PositionBuffer::testWawer5() {
	addPositionToBeTriggered(positionValidPKPWawer, 0, 1);
	addPositionToBeTriggered(positionValidPKPWawer, 1, 1);
	addPositionToBeTriggered(positionValidPKPWawer, 2, 1);
	addPositionToBeTriggered(positionValidPKPWawer, 3, 1);
	addPositionToBeTriggered(positionValidPKPWawer, 4, 1);
	addPositionToBeTriggered(positionValidPKPWawer, 5, 1);

	return averageFromRange(2, 1);
}

void PositionBuffer::testWawer4() {
	addPositionToBeTriggered(positionValidPKPWawer, 0, 3);
	addPositionToBeTriggered(positionValidPKPWawer, 1, 6);

}
#endif

#if 0
double PositionBuffer::testDistanceWawerWodynska1() {
	Position2 wawer = positionValidPKPWawer[0];
	Position2 wodynska = positionValidWodynska[0];
	return TinyGPS::distance_between(wawer.getLatitude(), wawer.getLongitude(), wodynska.getLatitude(), wodynska.getLongitude());
}
#endif

void PositionBuffer::tick() {

	if (millis() - oneSecondTimer > 1000) {
		oneSecondTimer = millis();
		//Serial.write('t');
		oneSecondTick();
	}
#if 0
	if (millis() - fifthSecondTimer > 1000) {
		fifthSecondTimer = millis();
		//Serial.write('t');
		fifthSecondTick();
	}
#endif

}

#if 0
void PositionBuffer::fifthSecondTick() {

	int i = 0;
	while (true) {
		Position2 p = positionsForTesting.get(i);
		if (!p.fired && p.triggerTime * 1000.0 > millis()) {
			p.fired = true;
			Serial.println("adding test position");
			//printDouble(p.latitude, 5);
			//addGPSPositionToOneSecondBuffers(p);
			updateCurrentSecondPosition(p);
			positionsForTesting.remove(i);
			i = 0;
			//positionsForTesting.set(i, p);
		}
		i++;
		if (i == positionsForTesting.size() - 1)
			break;
	}

	fifthSecondTimer = 0;
}
#endif

void PositionBuffer::addToHistory(Position2 p){

	//positions[writePos] = p;
	//writePos = nextForward(writePos);
	if(historyPositions.size() == 5)
		historyPositions.remove(4);

	historyPositions.add(0,p);

}

void PositionBuffer::oneSecondTick() {



	//addPositionToBeTriggered(positionValidPKPWawer, 0, 3);

	//int i = millis() % 10;

//	Position nowa;
//	nowa.fired = false;
//	nowa.numOfSats = i;
	//positionsForTesting.add(0, nowa);
	// adding test samples!
#if 0
	for(int numOfTestSamples = 0; numOfTestSamples < random(0,3); numOfTestSamples++){
		Position2 pos;
		pos.latitude = random(0,100)/100.0;
		pos.longitude = random(0,100)/100.0;
		pos.numOfSats = random(2,7);
		pos.hdop = (random(1,1000) / 1000.0);
		addGPSPositionToOneSecondBuffers(pos);
		//addGPSPositionToOneSecondBuffers(currentSecondPosition);
	}
#endif

	printStatsToSerialBefore();

	Position2 avg = averageFromCurrentSecPositionsAndCleanBuffer();
	addToHistory(avg);

	currentSecondPosition.resetPosition();

	printStatsToSerialAfter();
}

void PositionBuffer::printStatsToSerialBefore() {

	Serial.print(F("-fm ="));
	Serial.println(freeMemory2());
	Serial.print(F("one second tick"));
	Serial.print(F("pos in this second:"));
	Serial.println(positionsInCurrentSecond.size());

	//Serial.write('1');





}

void PositionBuffer::printStatsToSerialAfter() {


	//Serial.write('1');



#if 0
	Serial.println(positionsInCurrentSecond.size());
	for (int i = 0; i < positionsInCurrentSecond.size(); i++) {
		positionsInCurrentSecond.get(i).writeStatToSerial();
	}
#endif

#if 1
	Serial.println(F("history positions:"));
	Serial.println(historyPositions.size());
	for (int i = 0; i < historyPositions.size(); i++) {
		historyPositions.get(i).writeStatToSerial();
	}
#endif


}


#if 0
void PositionBuffer::addPositionToBeTriggered(Position2 *array, int index,
		float time) {

	//Position p(21.1, 21.2);

	Position2 &p = array[index];
	//printDouble(p.latitude, 5);
	p.triggerTime = time;
	positionsForTesting.add(p);
}
#endif

void addTestSamplesIfTriggeredByTime() {

}


Position2 PositionBuffer::averageFromCurrentSecPositionsAndCleanBuffer(){

	Position2 result;
#if 0
	while(positionsInCurrentSecond.size() > 0){
		Position2 p = positionsInCurrentSecond.remove(0);
	//	result = p;
	}
#endif

	double lat = 0.0;
	double longitude = 0.0;
	int nrOfSats= 0;
	double hdop = 0.0;

	int numOfValidSamples = 0;
	for(int i = 0; i < positionsInCurrentSecond.size(); i++){
		Position2 p = positionsInCurrentSecond.get(i);
		if(p.numOfSats < 3)
			continue;
		numOfValidSamples++;
		lat += p.latitude;
		longitude += p.longitude;
		nrOfSats += p.numOfSats;
		hdop += p.hdop;
	}



	lat = lat / (double)numOfValidSamples;
	longitude = longitude / (double)numOfValidSamples;
	hdop = hdop / (double)numOfValidSamples;

	positionsInCurrentSecond.clear();

	result.latitude = lat;
	result.longitude = longitude;
	result.numOfSats = nrOfSats;
	result.hdop = hdop;
	return result;

}

