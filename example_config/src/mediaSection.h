//
//  mediaSection.h
//  example_config
//
//  Created by Osiloke Emoekpere on 9/22/14.
//
//

#ifndef __example_config__mediaSection__
#define __example_config__mediaSection__

#include <iostream>
#include "sectionFactory.h"
#include "ofMain.h"

class VideoSection: public Section{
//Let the section factory know that you can be created dynamically
REGISTER_SECTION(VideoSection);
    ofVideoGrabber videoGrabber;
    ofPolyline polyline;
public:
    //Minimum constructor needed to use a section, This is assuming you are setting up sections from a section file
    VideoSection(const std::string key, const Json::Value data): Section(key, data){}
//    ~VideoSection(){}
    int getColor(){
        if(data.isMember("color")){
            Json::Value color = data["color"];
            if (color.isMember("hex")){
                return (int)strtol(color["hex"].asString().c_str(), NULL, 16);
            }
        }
        return 0;
    }
    void setup(){
        vector<ofVideoDevice> devices = videoGrabber.listDevices();
        
        for(int i = 0; i < devices.size(); i++){
            cout << devices[i].id << ": " << devices[i].deviceName;
            if( devices[i].bAvailable ){
                cout << endl;
            }else{
                cout << " - unavailable " << endl;
            }
        }
        videoGrabber.setDeviceID(0);
        videoGrabber.setDesiredFrameRate(30);
        bool init = videoGrabber.initGrabber(720, 480);
        polyline.lineTo(20,20);
        polyline.lineTo(40,20);
        polyline.lineTo(40,40);
        polyline.lineTo(20,40);
        polyline.close();
    }
    void onAttachedToParent(){
        /**
         Gets called immediately after this section has been attachd for the first time to a parent
         **/ 
        setup(); 
    }
    void onRefresh(){
        /**
         Called when parent has been altered and children need to be refreshed
         **/
    }
    void update(){ 
        videoGrabber.update();
    }
    void draw(){
        draw(x_pos.getValue().asInt(),y_pos.getValue().asInt(),width.getValue().asInt(),height.getValue().asInt());
    }
    void draw(int x, int y, int w, int h){ 
        //Draw whatever here, the x, y, w and h are handled by the parent section
        ofSetHexColor(getColor());
        ofNoFill();
        ofRect(x, y, w, h);
        ofSetColor(255, 255, 255); 
        videoGrabber.draw(x, y, w, h);
    };
};
#endif /* defined(__example_config__mediaSection__) */