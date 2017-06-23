#include "ofApp.h"

using namespace tri;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0);
    ofSetFrameRate(30);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    
    mSurfaceManager = SurfaceManager::create();
    
    mGrupos = GrupoManager::create();

    surfaceCounter      = 0;
    hoverParticle       = -1;
    viewSurfaces        = false;
    color1.set(255, 0, 0);
    color2.set(0, 150, 250, 100);
    particleSize = 2;
    midiInput.setup();
    
    loadJSON();
    
    setupGUI();
    
    setupMidi();
    
    fondo.load("fondo.jpg");
    mHideFondo = true;
    mHideGroupEditor = true;
    
    sequencerMode = 1;
    
    sifon.setName("sequencer1");
    
    for (int i = 0; i < 16; i++) {
        ofColor * tempColor = new ofColor(0, 0, 0);
        colores1.push_back(tempColor);
        int * tempVel = new int(0);
        velocidades1.push_back(tempVel);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    mGrupos->update(timer.getAppTimeMillis());
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < 16; i++){
        if (mGrupos->getGrupo(i)->getIsActive()) {
            mGrupos->getGrupo(i)->draw(0, 0, colores1[i]);
        }
        
    }
    sifon.publishScreen();
    
    
    if (!mHideFondo) {
        fondo.draw(0, 0, 1080, 1080);
    }
    
    if(!midiInput.mHideMidiInput){
        midiInput.draw();
    }
    
    if (viewSurfaces && !enableCreateSurface1) {
        mSurfaceManager->drawEditSurfaces(color1);
    }
    
    if(enableNewParticle3){
        mSurfaceManager->drawPoints(color1, particleSize);
    }
    else if(enableMoveParticle2){
        mSurfaceManager->drawPoints(color1, particleSize);
        if (mTempParticleId >= 0) {
            mSurfaceManager->drawMoveParticle(mTempParticleId, particleSize);
        }
        
    }
    else if(enableCreateSurface1){
        mSurfaceManager->drawPoints(color1, particleSize);
        mSurfaceManager->drawCreateSurface(editorTemporals, color1, color2, particleSize);
    }
    
    else if(enableNewGroup4 || enableDeleteGroup5){
        mSurfaceManager->drawPoints(color1, particleSize);
        mSurfaceManager->drawCreateSurface(editorTemporals, color1, color2, particleSize);
        tempGrupo->drawEdit(ofColor(200, 200, 200, 250));
        mGrupos->drawEditGrupos();
        mGrupos->drawInterface();
        if (temporal >= 0) {
            mGrupos->getGrupo(temporal)->drawEdit(ofColor(0, 220, 50, 190));
        }
    }
    
    if(!mHideGUI){
        gui.draw();
    }
    if (drawBoundingRectangle) {
        aux->drawBoundingBox();
    }
    
    ofPushStyle();
    ofSetColor(255, 0, 0);

        ofDrawBitmapString(isLess9, ofGetMouseX(), ofGetMouseY());
    
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case '1':
            sequencerMode = 1;                                          break;
        case '2':
            sequencerMode = 2;                                          break;
        case 'b':
            drawBoundingRectangle = !drawBoundingRectangle;             break;
        case 'c':
            clear();                                                    break;
        case 'e':
            
        case 'f':
            mHideFondo = !mHideFondo;                                   break;
        case 'g':
            mHideGUI = !mHideGUI;                                       break;
        case 'h':
            midiInput.changeMode();                                     break;
        case 'l':
            loadJSON();                                                 break;
        case 'p':
            mSurfaceManager->showPos();                                 break;
        case 's':
            saveJSON();                                                 break;
        case 'v':
            viewSurfaces = !viewSurfaces;                               break;
            case ' ':
            if (enableNewGroup4) {
                Grupo * grup = new Grupo();
                grup->setSurfaces(tempGrupo->getSurfaces());
                mGrupos->addGrupo(grup);
                tempGrupo->clear();
            }
    }
    if(key == OF_KEY_UP){
        if (enableMoveParticle2) {
            mSurfaceManager->updateParticlePos(toMove, mSurfaceManager->getParticle(toMove)->getPosition()-ofVec3f(0, 1, 0));
        }
        else if (enableNewParticle3 || enableCreateSurface1){
            particleSize++;
        }
    }
    if(key == OF_KEY_DOWN){
        if (enableMoveParticle2) {
            mSurfaceManager->updateParticlePos(toMove, mSurfaceManager->getParticle(toMove)->getPosition()+ofVec3f(0, 1, 0));
        }
        else if (enableNewParticle3 || enableCreateSurface1){
            particleSize--;
        }
    }
    if(key == OF_KEY_RIGHT){
        if (enableMoveParticle2) {
            mSurfaceManager->updateParticlePos(toMove, mSurfaceManager->getParticle(toMove)->getPosition()+ofVec3f(1, 0, 0));
        }
        else if (enableNewParticle3){
            if (color1 == ofColor(255, 0, 0)) {
                color1.set(0, 255, 0);
            }
            else if (color1 == ofColor(0, 255, 0)) {
                color1.set(0, 0, 255);
            }
            else if (color1 == ofColor(0, 0, 255)) {
                color1.set(255, 0, 0);
            }
        }
        else if (enableCreateSurface1) {
            if (color2 == ofColor(0, 150, 250)) {
                color2.set(250, 0, 150);
            }
            else if (color2 == ofColor(250, 0, 150)) {
                color2.set(150, 250, 0);
            }
            else if (color2 == ofColor(150, 250, 0)) {
                color2.set(0, 150, 250);
            }
        }

    }
    if(key == OF_KEY_LEFT){
        if (enableMoveParticle2) {
            mSurfaceManager->updateParticlePos(toMove, mSurfaceManager->getParticle(toMove)->getPosition()-ofVec3f(1, 0, 0));
        }
        else if (enableNewParticle3){
            if (color1 == ofColor(255, 0, 0)) {
                color1.set(0, 0, 255);
            }
            else if (color1 == ofColor(0, 255, 0)) {
                color1.set(255, 0, 0);
            }
            else if (color1 == ofColor(0, 0, 255)) {
                color1.set(0, 255, 0);
            }
        }
        else if (enableCreateSurface1) {
            if (color2 == ofColor(0, 150, 250)) {
                color2.set(150, 250, 0);
            }
            else if (color2 == ofColor(250, 0, 150)) {
                color2.set(0, 150, 250);
            }
            else if (color2 == ofColor(150, 250, 0)) {
                color2.set(250, 0, 150);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    if ((enableNewGroup4 || enableDeleteGroup5)
        && x > 500 && x < 940
        && y > 1083 && y < 1151) {
            temporal = mGrupos->isInside(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(enableMoveParticle2){
        if(mTempParticleId != -1){
            mSurfaceManager->updateParticlePos(mTempParticleId, ofVec3f(x, y, 0));
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    if(enableNewParticle3){
        Particle * particle = new Particle();
        particle->setPosition(ofVec3f(x, y, 0));
        mSurfaceManager->addParticle(particle);
    }
    else if(enableMoveParticle2){
        Particle * particle = mSurfaceManager->getNearestParticle(ofVec3f(x, y, 0));
        //found something
        if(particle != NULL){
            tempPart = particle->getPosition();
            mTempParticleId = particle->getParticleId();
            toMove = mTempParticleId;
            mSurfaceManager->updateParticlePos(mTempParticleId, ofVec3f(x, y, 0));

        }else{
            mTempParticleId = -1;
        }
    }
    else if(enableCreateSurface1){
        Particle * particle = mSurfaceManager->getNearestParticle(ofVec3f(x, y, 0));
        if(particle != NULL){
            if(surfaceCounter == 0){
                editorTemporals.push_back(particle->getParticleId());
            }
            else if(surfaceCounter == 1 && particle->getParticleId() != editorTemporals[0]){
                editorTemporals.push_back(particle->getParticleId());
            }
            if(surfaceCounter == 2 && particle->getParticleId() != editorTemporals[0] && particle->getParticleId() != editorTemporals[1]){
                editorTemporals.push_back(particle->getParticleId());
                
                Surface * sur = new Surface();
                sur->addParticle(mSurfaceManager->getParticle(editorTemporals[0]));
                sur->addParticle(mSurfaceManager->getParticle(editorTemporals[1]));
                sur->addParticle(mSurfaceManager->getParticle(editorTemporals[2]));
                editorTemporals.clear();

                mSurfaceManager->addSurface(sur);
                mSurfaceManager->clearVectors();
            }
            
            surfaceCounter++;
            if(surfaceCounter >=3 )
                surfaceCounter = 0;
        }
    }
    else if(enableNewGroup4){
        for (int i = 0; i < mSurfaceManager->getNumberOfSurfaces(); i++) {
            if (mSurfaceManager->getSurface(i)->isPointInTriangle(ofVec2f(x, y))) {
                tempGrupo->addSurface(mSurfaceManager->getSurface(i));
                break;
            }
        }
    }
    else if (enableDeleteGroup5){
        if (mGrupos->isInside(x, y) == temporal) {
            mGrupos->deleteGroup(temporal);
            temporal = -1;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(enableMoveParticle2){
        if(mTempParticleId != -1){
            mSurfaceManager->updateParticlePos(mTempParticleId, ofVec3f(x, y, 0));
        }
    }
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

//--------------------------------------------------------------
void ofApp::clearMesh(){
    mSurfaceManager->cleanMesh();
}

//--------------------------------------------------------------
void ofApp::setupGUI(){
    
    gui.setup("GUI");
    mButtonResetMesh.addListener(this, &ofApp::clearMesh);
    gui.add(mButtonResetMesh.setup("Reset Mesh"));
    
    gui.add(drawBoundingRectangle.setup("Bounding rectangle", false));
    gui.add(enableNewParticle3.setup("New Particle", false));
    gui.add(enableMoveParticle2.setup("Move Particle", false));
    gui.add(enableCreateSurface1.setup("Create Surface", false));
    gui.add(enableNewGroup4.setup("New Group", false));
    gui.add(enableDeleteGroup5.setup("Delete Group", false));
    
    mHideGUI = true;

}

//--------------------------------------------------------------
void ofApp::saveJSON(){
    mJSON.clear();
    
    if(int particleNumber = mSurfaceManager->getNumberOfParticles()){
        Json::Value points(Json::arrayValue);
        for (int j = 0; j < particleNumber; j++){
            Json::Value pos(Json::objectValue);
            pos["x"] = mSurfaceManager->getParticle(j)->getPosition().x;
            pos["y"] = mSurfaceManager->getParticle(j)->getPosition().y;
            points.append(pos);
        }
        
        mJSON["Particles"]  = points;
        if (!mJSON.save("Particles.json", true)){
            ofLogNotice("ofApp::setup") << "Particles.json written unsuccessfully.";
        }
        else{
            ofLogNotice("ofApp::setup") << "Particles.json written successfully.";
        }
    }
    
    mJSON.clear();
    
    if (mSurfaceManager->getNumberOfSurfaces()) {
        Json::Value points(Json::arrayValue);
        for (int i = 0; i < mSurfaceManager->getNumberOfSurfaces(); i++){
            Json::Value pos(Json::objectValue);
            pos["A"] = mSurfaceManager->getSurface(i)->getIndex(0);
            pos["B"] = mSurfaceManager->getSurface(i)->getIndex(1);
            pos["C"] = mSurfaceManager->getSurface(i)->getIndex(2);
            points.append(pos);
        }
        mJSON["Surfaces"]  = points;
    }
    
    
    if (!mJSON.save("Surfaces.json", true)){
        ofLogNotice("ofApp::setup") << "Surfaces.json written unsuccessfully.";
    }
    else{
        ofLogNotice("ofApp::setup") << "Surfaces.json written successfully.";
    }
    
    mJSON.clear();
    
    if (mGrupos->getNumberOfGroups()) {
        Json::Value points(Json::arrayValue);
        for (int i = 0; i < mGrupos->getNumberOfGroups(); i++){
            Json::Value pos(Json::objectValue);
            Grupo * grup = mGrupos->getGrupo(i);
            pos["length"] = grup->getSize();
            for (int j = 0; j < mGrupos->getGrupo(i)->getSize(); j++) {
                pos["g" + ofToString(j)] = grup->getSurface(j)->getSurfaceIndex();
            }
            points.append(pos);
        }
        mJSON["Grupos"]  = points;
    }
    
    
    if (!mJSON.save("Grupos.json", true)){
        ofLogNotice("ofApp::setup") << "Grupos.json written unsuccessfully.";
    }
    else{
        ofLogNotice("ofApp::setup") << "Grupos.json written successfully.";
    }
}

//--------------------------------------------------------------
void ofApp::loadJSON(){
    std::string file;
    file = "Particles.json";
    bool parsingSuccessful = mJSON.open(file);
    if(parsingSuccessful){
        ofLogNotice("ofApp::setup") << "successfully read: "<<file<<std::endl;
    }else{
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << std::endl;
    }
    
    for (const Json::Value & points : mJSON["Particles"])  // iterate over "points"
    {
        float px   = points["x"].asFloat();
        float py   = points["y"].asFloat();
        
        Particle * tmpParticle = new Particle();
        tmpParticle->setPosition(ofVec3f(px, py, 0));
        
        mSurfaceManager->addParticle(tmpParticle);
    }
    
    file = "Surfaces.json";
    parsingSuccessful = mJSON.open(file);
    if(parsingSuccessful){
        ofLogNotice("ofApp::setup") << "successfully read: "<<file<<std::endl;
    }else{
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << std::endl;
    }
    
    for (const Json::Value & points : mJSON["Surfaces"])
    {
        int A    = points["A"].asInt();
        int B    = points["B"].asInt();
        int C    = points["C"].asInt();

        Surface * sur = new Surface();
        sur->addParticle(mSurfaceManager->getParticles()[A]);
        sur->addParticle(mSurfaceManager->getParticles()[B]);
        sur->addParticle(mSurfaceManager->getParticles()[C]);
        mSurfaceManager->addSurface(sur);

    }
    
    file = "Grupos.json";
    parsingSuccessful = mJSON.open(file);
    if(parsingSuccessful){
        ofLogNotice("ofApp::setup") << "successfully read: "<<file<<std::endl;
    }else{
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << std::endl;
    }
    
    for (const Json::Value & points : mJSON["Grupos"])
    {
        int length    = points["length"].asInt();
        Grupo * grup = new Grupo();
        for (int i = 0; i < length; i++) {
            int newIndex = points["g" + ofToString(i)].asInt();
            grup->addSurface(mSurfaceManager->getSurface(newIndex));
        }
        
        mGrupos->addGrupo(grup);
    }
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg){
    
    if (msg.portNum == 1) {
        if (sequencerMode == 1) {
            if (msg.status == MIDI_NOTE_ON) {
                
                int p = msg.pitch - 60;
                if (p < mGrupos->getNumberOfGroups()) {
                    mGrupos->getGrupo(p)->setActive(timer.getAppTimeMillis(), msg.velocity);
                }
            }else {
                //
            }
        }
        
        if(msg.status == 248){
            midiInput.newClockMessage();
        }
        else if(msg.status == MIDI_START) {
            
            midiInput.newStartMessage();
            
        }
    }
    else{
        //ofLogNotice("ofApp::newMidiMessage") << "pitch: "<<msg.pitch<<"vale"<<msg.value<<"status"<<msg.status;
        if (msg.status == 144 && msg.pitch == 17) {
            isLess9 = !isLess9;
        }
        int control = msg.control;
        if (!isLess9) {
            control += 24;
            
        }
        if (control < 48) {
            int value = msg.value -64;
            if(control % 3 == 0){
                if (colores1[control/3]->r + value < 0) {
                    colores1[control/3]->r = 0;
                }else if(colores1[control/3]->r + value > 255){
                    colores1[control/3]->r = 255;
                }else{
                    colores1[control/3]->r = colores1[control/3]->r + value;
                }
                ofLogNotice("ofApp::newMidiMessage") << "control"<<colores1[control/3]->r;
            }
            else if(control % 3 == 1){
                if (colores1[control/3]->g + value < 0) {
                    colores1[control/3]->g = 0;
                }else if(colores1[control/3]->g + value > 255){
                    colores1[control/3]->g = 255;
                }else{
                    colores1[control/3]->g = colores1[control/3]->g+ value;
                }
            }
            else if(control % 3 == 2){
                if (colores1[control/3]->b + value < 0) {
                    colores1[control/3]->b = 0;
                }else if(colores1[control/3]->b + value > 255){
                    colores1[control/3]->b = 255;
                }else{
                    colores1[control/3]->b = colores1[control/3]->b+ value;
                }
            }
        }
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::setupMidi(){
    sparkPublic.listPorts(); // via instance
    //ofxMidiIn::listPorts(); // via static as well
    
    // open port by number (you may need to change this)
    sparkPublic.openPort(1);
    //midiIn.openPort("IAC Driver Bus 1");	// by name
    //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
    
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    sparkPublic.ignoreTypes(false, false, false);
    sparkPublic.addListener(this);

    // print received messages to the console
    sparkPublic.setVerbose(false);
    
    //------Private Spark Input
    sparkPrivate.listPorts();
    sparkPrivate.openPort(4);
    sparkPrivate.ignoreTypes(false, false, false);
    sparkPrivate.setVerbose(false);
    sparkPrivate.addListener(this);
}

//--------------------------------------------------------------
void ofApp::clear(){
    mSurfaceManager->cleanMesh();
    mSurfaceManager->clear();
    
}

//--------------------------------------------------------------
void ofApp::exit() {
    
    // clean up
    sparkPublic.closePort();
    
    sparkPrivate.closePort();
}
