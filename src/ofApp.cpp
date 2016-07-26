#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true); //画面の初期設定
    
    cam.setOrientation(ofPoint(-20,0,0)); //カメラの初期設定
    
    //GL設定
    glEnable(GL_DEPTH_TEST); //深さを有効
    glEnable(GL_NORMALIZE);  //法線ベクトルの自動正規化
    
    leap.open(); //LeapMotionの開始。
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    SimpleHands = leap.getSimpleHands(); //検出された手の数だけ、ofxLeapMotionSimpleHandのvector配列に追加
    if(leap.isFrameNew() && SimpleHands.size() ){  //もしフレーム更新して、手が検出されたら
        fingerPos.clear(); //今保存されている指の位置をクリア
        
        handPos.clear(); //今保存されている手の中心の位置座標をクリア
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2); //画面の大きさに合わせてスケールをマッピング。
        leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
    
        leap.setMappingZ(-150, 150, -200, 200);
        
        
        fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
        
        for(int i = 0; i<SimpleHands.size(); i++) { //検出された手の繰り返し。
            
            handPos.push_back(SimpleHands[i].handPos); //手の中心座標をvector配列に追加(手の数だけ行う)
            
            for(int f = 0; f<5; f++) { //手の関節を描画するためのfor文。
                ofPoint mcp = SimpleHands[i].fingers[ fingerTypes[f] ].mcp; //metacarpal(手の中心側)
                fingerPos.push_back(mcp); //fingerPosをvector配列に追加。
                
                ofPoint pip = SimpleHands[i].fingers[ fingerTypes[f] ].pip; //metacarpal(手の中心側)
                fingerPos.push_back(pip); //fingerPosをvector配列に追加。
                
                ofPoint dip = SimpleHands[i].fingers[ fingerTypes[f] ].dip; //metacarpal(手の中心側)
                fingerPos.push_back(dip); //fingerPosをvector配列に追加。
                
                ofPoint tip = SimpleHands[i].fingers[ fingerTypes[f] ].tip; //metacarpal(手の中心側)
                fingerPos.push_back(tip); //fingerPosをvector配列に追加。
                }
        }
    }

    leap.markFrameAsOld(); //ofxLeapMotionに現在のフレームが古くなったことを通知
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    cam.begin();
    for (int i = 0; i < SimpleHands.size(); i++){ //手の数だけfor文を回す。
        ofSetColor(0, 255, 100);
        ofDrawSphere(handPos.at(i),20);
        
        for (int f = 0; f < 5; f++) { //手の関節を描画するためのfor文。
            
            ofSetColor(255);
            ofDrawSphere(fingerPos.at(20*i+4*f+0), 10); //mcp(手の最も中心側)
            
            ofSetColor(200);
            ofDrawSphere(fingerPos.at(20*i+4*f+1), 10); //pip(手の二番目に中心側)
            
            ofSetColor(155);
            ofDrawSphere(fingerPos.at(20*i+4*f+2), 10); //dip(手の指先の一歩手前)
            
            ofSetColor(100);
            ofDrawSphere(fingerPos.at(20*i+4*f+3), 10); //tip(手の指先)
            
            ofLine(fingerPos.at(20*i+4*f+0),fingerPos.at(20*i+4*f+1));
            ofLine(fingerPos.at(20*i+4*f+1),fingerPos.at(20*i+4*f+2));
            ofLine(fingerPos.at(20*i+4*f+2),fingerPos.at(20*i+4*f+3));
            
        }
        
    }
    if (SimpleHands.size() ==2 ) {
        float distance = sqrt(pow(handPos.at(0).x-handPos.at(1).x,2)
                              +pow(handPos.at(0).y-handPos.at(1).x,2)
                              +pow(handPos.at(0).z-handPos.at(1).z,2));
        
        ofSetColor(227,100);
        ofDrawSphere((handPos.at(0).x+handPos.at(1).x)/2,
                     (handPos.at(0).y+handPos.at(1).y)/2,
                     (handPos.at(0).z+handPos.at(1).z)/2,
                     distance/2);
    }
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
