#include "MyForm.h"
#include <myo/myo.hpp>

using namespace Project4;

// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <chrono>

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))


// Classes that inherit from myo::DeviceListener can be used to receive events from Myo devices. DeviceListener
// provides several virtual functions for handling different kinds of events. If you do not override an event, the
// default behavior is to do nothing.

class DataCollector : public myo::DeviceListener {
public:
	DataCollector()
		: onArm(false), roll_w(0), pitch_w(0), yaw_w(0), currentPose()
	{
	}

	void onPair(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
	{
		// Print out the MAC address of the armband we paired with.

		// The pointer address we get for a Myo is unique - in other words, it's safe to compare two Myo pointers to
		// see if they're referring to the same Myo.

		// Add the Myo pointer to our list of known Myo devices. This list is used to implement identifyMyo() below so
		// that we can give each Myo a nice short identifier.
		knownMyos.push_back(myo);

		// Now that we've added it to our list, get our short ID for it and print it out.
		std::cout << "Paired with " << identifyMyo(myo) << "." << std::endl;
	}

	// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
	void onUnpair(myo::Myo* myo, uint64_t timestamp)
	{
		if (1 == identifyMyo(myo)) {

			// We've lost a Myo.
			// Let's clean up some leftover state.
			roll_w = 0;
			pitch_w = 0;
			yaw_w = 0;
			onArm = false;
		}
		else {
			roll_w2 = 0;
			pitch_w2 = 0;
			yaw_w2 = 0;
			onArm2 = false;
		}
	}

	// onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
	// as a unit quaternion.
	void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
	{
		using std::atan2;
		using std::asin;
		using std::sqrt;
		using std::max;
		using std::min;

		// Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
		float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
			1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
		float pitch = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));
		float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
			1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));

		if (1 == identifyMyo(myo)) {
			roll_w = static_cast<int>((roll + (float)3.14) / (3.14 * 2.0f) * 18);
			pitch_w = static_cast<int>((pitch + (float)3.14 / 2.0f) / 3.14 * 18);
			yaw_w = static_cast<int>((yaw + (float)3.14) / (3.14 * 2.0f) * 18);
		}
		else {
			//M_PI doesnt work
			// Convert the floating point angles in radians to a scale from 0 to 18.
			roll_w2 = static_cast<int>((roll + (float)3.14) / (3.14 * 2.0f) * 18);
			pitch_w2 = static_cast<int>((pitch + (float)3.14 / 2.0f) / 3.14 * 18);
			yaw_w2 = static_cast<int>((yaw + (float)3.14) / (3.14 * 2.0f) * 18);
		}
	}

	// onPose() is called whenever the Myo detects that the person wearing it has changed their pose, for example,
	// making a fist, or not making a fist anymore.
	void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
	{
		if (1 == identifyMyo(myo)) {
			currentPose = pose;
		}
		else {
			currentPose2 = pose;
		}
		myo->unlock(myo::Myo::unlockHold);

		// Notify the Myo that the pose has resulted in an action, in this case changing
		// the text on the screen. The Myo will vibrate.
		myo->notifyUserAction();
	}

	// onArmSync() is called whenever Myo has recognized a Sync Gesture after someone has put it on their
	// arm. This lets Myo know which arm it's on and which way it's facing.
	void onArmSync(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection)
	{
		if (1 == identifyMyo(myo)) {

			onArm = true;
			whichArm = arm;
		}
		else {
			onArm2 = true;
			whichArm2 = arm;
		}
	}

	// onArmUnsync() is called whenever Myo has detected that it was moved from a stable position on a person's arm after
	// it recognized the arm. Typically this happens when someone takes Myo off of their arm, but it can also happen
	// when Myo is moved around on the arm.
	void onArmUnsync(myo::Myo* myo, uint64_t timestamp)
	{
		if (1 == identifyMyo(myo)) {
			onArm = false;
		}
		else
		{
			onArm2 = false;
		}
	}

	// There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
	// For this example, the functions overridden above are sufficient.

	// We define this function to print the current values that were updated by the on...() functions above.
	void print()
	{

		// Clear the current line
		std::cout << '\r';

		// Print out the orientation. Orientation data is always available, even if no arm is currently recognized.

		
		/*std::cout
			<< std::string(std::to_string(roll_w))  <<  '[' << std::string(roll_w, '*') << std::string(18 - roll_w,  ' ') << ']'
			<< std::string(std::to_string(pitch_w)) << '[' << std::string(pitch_w, '*') << std::string(18 - pitch_w, ' ') << ']'
			<< std::string(std::to_string(yaw_w))   << '[' << std::string(yaw_w,   '*') << std::string(18 - yaw_w,   ' ') << ']';*/

		std::cout
			<< '[' << std::string(roll_w, '*') << std::string(18 - roll_w, ' ') << ']'
			<< '[' << std::string(pitch_w, '*') << std::string(18 - pitch_w, ' ') << ']'
			<< '[' << std::string(yaw_w, '*') << std::string(18 - yaw_w, ' ') << ']';
		
		if (onArm) {
			// Print out the currently recognized pose and which arm Myo is being worn on.

			// Pose::toString() provides the human-readable name of a pose. We can also output a Pose directly to an
			// output stream (e.g. std::cout << currentPose;). In this case we want to get the pose name's length so
			// that we can fill the rest of the field with spaces below, so we obtain it as a string using toString().
			std::string poseString = currentPose.toString();

			std::cout << '[' << (whichArm == myo::armLeft ? "L" : "R") << ']'
				<< '[' << poseString << std::string(14 - poseString.size(), ' ') << ']';
		}
		else {
			// Print out a placeholder for the arm and pose when Myo doesn't currently know which arm it's on.
			std::cout << "[?]" << '[' << std::string(14, ' ') << ']' << '\n';
		}



	std::cout << '[' << std::string(roll_w2, '*') << std::string(18 - roll_w2, ' ') << ']'
			<< '[' << std::string(pitch_w2, '*') << std::string(18 - pitch_w2, ' ') << ']'
			<< '[' << std::string(yaw_w2, '*') << std::string(18 - yaw_w2, ' ') << ']';

	if (onArm2) {
		// Print out the currently recognized pose and which arm Myo is being worn on.

		// Pose::toString() provides the human-readable name of a pose. We can also output a Pose directly to an
		// output stream (e.g. std::cout << currentPose;). In this case we want to get the pose name's length so
		// that we can fill the rest of the field with spaces below, so we obtain it as a string using toString().
		std::string poseString = currentPose2.toString();

		std::cout << '[' << (whichArm2 == myo::armLeft ? "L" : "R") << ']'
			<< '[' << poseString << std::string(14 - poseString.size(), ' ') << ']';
	}
	else {
		// Print out a placeholder for the arm and pose when Myo doesn't currently know which arm it's on.
		std::cout << "[?]" << '[' << std::string(14, ' ') << ']';
	}

		//char rollPitchChars[] = { 'P', (char)roll_w,(char)pitch_w, '!' };

		//std::string rollpitchyawString(rollPitchChars);
		//String^ rollPitchStorageString = gcnew String(rollpitchyawString.c_str());

		//std::cout << rollpitchyawString;

		std::cout << std::flush;
	}

	// This is a utility function implemented for this sample that maps a myo::Myo* to a unique ID starting at 1.
	// It does so by looking for the Myo pointer in knownMyos, which onPair() adds each Myo into as it is paired.
	size_t identifyMyo(myo::Myo* myo) {
		// Walk through the list of Myo devices that we've seen pairing events for.
		for (size_t i = 0; i < knownMyos.size(); ++i) {
			// If two Myo pointers compare equal, they refer to the same Myo device.
			if (knownMyos[i] == myo) {
				return i + 1;
			}
		}

		return 0;
	}

	// We store each Myo pointer that we pair with in this list, so that we can keep track of the order we've seen
	// each Myo and give it a unique short identifier (see onPair() and identifyMyo() above).
	std::vector<myo::Myo*> knownMyos;

	// These values are set by onArmSync() and onArmUnsync() above.
	bool onArm;
	bool onArm2;
	myo::Arm whichArm;
	myo::Arm whichArm2;

	// These values are set by onOrientationData() and onPose() above.
	int roll_w, pitch_w, yaw_w;
	int roll_w2, pitch_w2, yaw_w2;

	myo::Pose currentPose;
	myo::Pose currentPose2;
};

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main()
{
	//MyForm frm1;
	MyForm^ frm1 = gcnew MyForm;
	frm1->ShowDialog();

	// We catch any exceptions that might occur below -- see the catch statement for more details.
	try {

		// First, we create a Hub with our application identifier. Be sure not to use the com.example namespace when
		// publishing your application. The Hub provides access to one or more Myos.
		myo::Hub hub("com.jakechapeskie.SerialCommunication");

		std::cout << "Attempting to find a Myo..." << std::endl;

		// Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
		// immediately.
		// waitForAnyMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
		// if that fails, the function will return a null pointer.
		myo::Myo* myo = hub.waitForMyo(10000);

		// If waitForAnyMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
		if (!myo) {
			throw std::runtime_error("Unable to find a Myo!");
		}

		// We've found a Myo.
		std::cout << "Connected to a Myo armband!" << std::endl << std::endl;


		// Next we construct an instance of our DeviceListener, so that we can register it with the Hub.
		DataCollector collector;

		// Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
		// Hub::run() to send events to all registered device listeners.
		hub.addListener(&collector);

		// Finally we enter our main loop.
		if (frm1->LockingEnalbed)
		{
			hub.setLockingPolicy(myo::Hub::LockingPolicy::lockingPolicyStandard);
		}
		else
		{
			hub.setLockingPolicy(myo::Hub::LockingPolicy::lockingPolicyNone);
		}

		int rollMin, rollMax, pitchMin, pitchMax;
		int leftMax = 0, rightMax = 0, forwardMax = 0, backwardsMax = 0;

		int rollMin2, rollMax2, pitchMin2, pitchMax2;
		int leftMax2 = 0, rightMax2 = 0, forwardMax2 = 0, backwardsMax2 = 0;


		// CALIBRATE PLAYER A
		std::cout << "Calibrating Player A Myo" << std::endl;

		// Calibrate left turn
		std::cout << "Hold arm straight out, rotate left" << std::endl;
		for (int i = 5; i > 0; i--) {
			std::cout << i << "...";
			_sleep(500);
		}
		hub.run(1000 / 20);
		leftMax = collector.roll_w;
		std::cout << "Calibrated Left Turn." << std::endl;

		// Calibrate right turn
		std::cout << "Hold arm straight out, rotate right" << std::endl;
		for (int i = 5; i > 0; i--) {
			std::cout << i << "...";
			_sleep(500);
		}
		hub.run(1000 / 20);
		rightMax = collector.roll_w;
		std::cout << "Calibrated Right Turn." << std::endl;
		
		// Calibrate forward movement
		std::cout << "Hold arm up, neutral rotation" << std::endl;
		for (int i = 5; i > 0; i--) {
			std::cout << i << "...";
			_sleep(500);
		}
		hub.run(1000 / 20);
		forwardMax = collector.pitch_w;
		std::cout << "Calibrated Forward Movement." << std::endl;

		// Calibrate backwards movement
		std::cout << "Hold arm down, neutral rotation" << std::endl;
		for (int i = 5; i > 0; i--) {
			std::cout << i << "...";
			_sleep(500);
		}
		hub.run(1000 / 20);
		backwardsMax = collector.pitch_w;
		std::cout << "Calibrated Backwards Movement." << std::endl;

		std::cout << "Calibrating Finished" << std::endl;

		std::cout << "left threshold = " << leftMax << ", right threshold = " << rightMax << std::endl;
		std::cout << "forward threshold" << forwardMax << ", backwards threshold = " << backwardsMax << std::endl;


		// CALIBRATE PLAYER B MYO
		std::cout << "Calibrating Player B Myo" << std::endl;

		// Calibrate left turn
		std::cout << "Hold arm straight out, rotate left" << std::endl;
		for (int i = 5; i > 0; i--) {
			std::cout << i << "...";
			_sleep(500);
		}
		hub.run(1000 / 20);
		leftMax2 = collector.roll_w2;
		std::cout << "Calibrated Left Turn." << std::endl;

		// Calibrate right turn
		std::cout << "Hold arm straight out, rotate right" << std::endl;
		for (int i = 5; i > 0; i--) {
			std::cout << i << "...";
			_sleep(500);
		}
		hub.run(1000 / 20);
		rightMax2 = collector.roll_w2;
		std::cout << "Calibrated Right Turn." << std::endl;

		// Calibrate forward movement
		std::cout << "Hold arm up, neutral rotation" << std::endl;
		for (int i = 5; i > 0; i--) {
			std::cout << i << "...";
			_sleep(500);
		}
		hub.run(1000 / 20);
		forwardMax2 = collector.pitch_w2;
		std::cout << "Calibrated Forward Movement." << std::endl;

		// Calibrate backwards movement
		std::cout << "Hold arm down, neutral rotation" << std::endl;
		for (int i = 5; i > 0; i--) {
			std::cout << i << "...";
			_sleep(500);
		}
		hub.run(1000 / 20);
		backwardsMax2 = collector.pitch_w2;
		std::cout << "Calibrated Backwards Movement." << std::endl;

		std::cout << "Calibrating Finished" << std::endl;

		std::cout << "left threshold = " << leftMax2 << ", right threshold = " << rightMax2 << std::endl;
		std::cout << "forward threshold" << forwardMax2 << ", backwards threshold = " << backwardsMax2 << std::endl;



		while (1) {

			// In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
			// In this case, we wish to update our display 20 times a second, so we run for 1000/20 milliseconds.
			hub.run(1000 / 20);
			// After processing events, we call the print() member function we defined above to print out the values we've
			// obtained from any events that have occurred.

			//collector.print();

			std::string poseString = (collector.currentPose.toString());
			std::string poseString2 = (collector.currentPose2.toString());
			 
			String^ poseStorageString = gcnew String(poseString.c_str());
			String^ poseStorageString2 = gcnew String(poseString2.c_str());

			//frm1->sendDataOverComm(poseStorageString);

			// cannot be integer 0, else (char)0 effectively becomes premature null terminator of string
			char dropHammer = (poseString.find("fingersSpread") != std::string::npos) ? '1' : '0';
			char dropHammer2 = (poseString2.find("fingersSpread") != std::string::npos) ? '1' : '0';

			int turnVal = map(collector.roll_w, leftMax, rightMax, 1, 101);
			int turnVal2 = map(collector.roll_w2, leftMax2, rightMax2, 1, 101);
			int fbVal = map(collector.pitch_w, forwardMax, backwardsMax, 1, 101);
			int fbVal2 = map(collector.pitch_w2, forwardMax2, backwardsMax2, 1, 101);

			turnVal = constrain(turnVal, 1, 101);
			fbVal   = constrain(fbVal,   1, 101);
			turnVal2 = constrain(turnVal2, 1, 101);
			fbVal2 = constrain(fbVal2, 1, 101);

			if (fbVal <= 51) {
				turnVal = 51;
			}
			if (fbVal2 <= 51) {
				turnVal2 = 51;
			}

			//std::cout << "turnVal: " << (int)((char)turnVal) << ", fbVal: " << (int)((char)fbVal) << ", hammer: " << dropHammer << std::endl;
			//std::cout << "turnVal: " << (int)((char)turnVal)-51 << ", fbVal: " << (int)((char)fbVal)-51 << ", hammer: " << dropHammer << std::endl;
			//std::cout << "turnVal: " << (int)((unsigned char)((char)turnVal)) << ", fbVal: " << (int)((unsigned char)((char)fbVal)) << ", hammer: " << dropHammer << std::endl;
			//std::cout << "turnVal: " << ((int)((char)turnVal)) << ", fbVal: " << ((int)((char)fbVal)) << ", hammer: " << ((int)((char)dropHammer));


			char rollPitchChars[] = { 'S', (char)turnVal, (char)fbVal, dropHammer, '!' };
			char rollPitchChars2[] = { 'S', (char)turnVal2, (char)fbVal2, dropHammer2, '!' };

			std::string rollpitchyawString(rollPitchChars);
			String^ rollPitchStorageString = gcnew String(rollpitchyawString.c_str());

			std::string rollpitchyawString2(rollPitchChars2);
			String^ rollPitchStorageString2 = gcnew String(rollpitchyawString2.c_str());

			frm1->sendDataOverComm(1, rollPitchStorageString);
			frm1->sendDataOverComm(2, rollPitchStorageString2);



			//frm1->sendDataOverComm(rollPitchChars, 5);
						
		}

		// If a standard exception occurred, we print out its message and exit.
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Press enter to continue.";
		std::cin.ignore();
		return 1;
	}


}
