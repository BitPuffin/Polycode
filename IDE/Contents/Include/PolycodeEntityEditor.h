/*
 Copyright (C) 2013 by Isak Andersson
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#pragma once

#include "PolycodeEditor.h"
#include <Polycode.h>
#include <PolycodeUI.h>
#include "PolycodeProps.h"

using namespace Polycode;

#ifdef _WINDOWS
#define round (int)
#endif

class EntityBrowserData  {
	public:
		Entity *entity;
};

class PolycodeEntityEditorActionDataEntry {
	public:
		PolycodeEntityEditorActionDataEntry(){
			entity = NULL;
			parentEntity = NULL;
		}
		PolycodeEntityEditorActionDataEntry(Vector3 vec3, Number number);	
		PolycodeEntityEditorActionDataEntry(Vector3 vec3);
		PolycodeEntityEditorActionDataEntry(Number number);
		PolycodeEntityEditorActionDataEntry(Entity *entity);
		Vector3 vec3;
		Number number;
		Entity *entity;
		Entity *parentEntity;		
};

class PolycodeEntityEditorActionData : public PolycodeEditorActionData {
	public:
		PolycodeEntityEditorActionData() {
			reverse = true;
		}
		virtual ~PolycodeEntityEditorActionData(){}
		
		std::vector<PolycodeEntityEditorActionDataEntry> entries;
		PolycodeEntityEditorActionDataEntry entry;
		bool reverse;
};

class EntityTreeView : public UIElement {
	public:
		EntityTreeView(Entity *rootEntity);
		~EntityTreeView();
		
		void Resize(Number width, Number height);
		void handleEvent(Event *event);	
		
		void syncNodeToEntity(UITree *node, Entity *entity);
		
		void setRootEntity(Entity *entity);
		
		void Refresh();

		Entity *selectedEntity;
		Entity *targetLayer;
		
		UIImageButton *newLayerButton;
		UIImageButton *targetLayerButton;
		
						
	protected:	
	
		Entity *rootEntity;
			
		bool dontSendSelectionEvent;
	
		UITreeContainer *treeContainer;
			
		ScreenShape *headerBg;		
		ScreenShape *bg;		
				
};

class PropertiesSizer : public UIElement {
	public:
		PropertiesSizer();
		~PropertiesSizer();
		
		void Resize(Number width, Number height);
		
		UIVSizer *sizer;
};


class EntityNameDisplay : public Entity {
	public:
		EntityNameDisplay(Entity *targetEntity);
		~EntityNameDisplay();
		
		void Update();
		
		ScreenLabel *label;
		ScreenLabel *tagsLabel;		
		Entity *targetEntity;
};

class PolycodeEntityEditorMain : public UIElement {
	public:
		
		PolycodeEntityEditorMain(PolycodeEditor *editor);
		virtual ~PolycodeEntityEditorMain();	
			
		void Resize(Number width, Number height);	
		void syncTransformToSelected();	
		Entity *addNewLayer(String layerName);	
		void updateCursor();		
		void selectEntity(Entity *entity, bool doAction = true);
		void resetSelectedEntityTransforms();
		void setMode(int newMode);	
		void handleEvent(Event *event);	
		void resizePreviewScreen();		
		void handleDroppedFile(OSFileEntry file, Number x, Number y);		
		bool hasSelected(Entity *entity);
		
		void deleteEntity(Entity *entity);
	
		void applyEditorOnly(Entity *entity);
		void applyEditorOnlyChildren(Entity *entity);
		void applyEditorProperties(Entity *entity);
			
		void processEventForEntity(Entity *childEntity, InputEvent *inputEvent);
	
		void createParticleRef(ScreenParticleEmitter *target);
		void createSoundRef(ScreenSound *target);
		void createEntityRef(Entity *entity);
		
		void doAction(String actionName, PolycodeEditorActionData *data);
		
		void setRefVisibility(bool val);
		void setEntityRefVisibility(Entity *entity, bool val);
		
		void getCenterAndSizeForSelected(Vector2 *center, Number *width, Number *height);
	
		void handleMouseDown(Vector2 position);
		void handleMouseMove(Vector2 position);
		void handleMouseUp(Vector2 position);
		
		void setGrid(int gridSize);
		
		void adjustForSnap(Vector2 *position);
		
		void setCurrentLayer(Entity *newLayer, bool doAction = true);
		Entity *getCurrentLayer();
		
		String Copy(void **data);
		void Paste(void *data, String clipboardType);
		void destroyClipboardData(void *data, String type);
		
		static const int MODE_SELECT = 0;
		static const int MODE_SHAPE = 1;
		static const int MODE_ZOOM = 2;
		static const int MODE_PAN = 3;
		static const int MODE_IMAGE = 4;
		static const int MODE_TEXT = 5;
		static const int MODE_PARENT = 6;
		static const int MODE_ENTITY = 7;
		static const int MODE_SOUND = 8;
		static const int MODE_LINK = 9;
		static const int MODE_SPRITE = 10;
		static const int MODE_PARTICLES = 11;
																
		std::vector<Entity*> layers;
		
		PropList *entityProps;
		
		Entity *layerBaseEntity;		
						
//		Entity *selectedEntity;
		std::vector<Entity*> selectedEntities;		
		
		Transform2DSheet *transform2dSheet;
		EntitySheet *entitySheet;
		ShapeSheet *shapeSheet;
		ScreenImageSheet *imageSheet;
		ScreenLabelSheet *labelSheet;
		SoundSheet *soundSheet;
		EntityPropSheet *entityPropSheet;
		EntityInstanceSheet *instanceSheet;
		ScreenSpriteSheet *spriteSheet;
		ScreenParticleSheet *particleSheet;
		EntitySheet *screenEntitySheet;
		
		EntityTreeView *treeView;
		
		Entity *objectBaseEntity;		
		Entity *placingPreviewEntity;												
		bool multiSelect;
		
		PolycodeEditor *editor;	
		Entity *baseEntity;			
	protected:
	
		PolycodeEntityEditorActionData *beforeData;
		Entity *currentLayer;	
	
		int gridSize;
		bool gridSnap;
		
		bool pixelSnap;
	
		ScreenShape *previewShape;
		ScreenImage *previewImage;
		EntityInstance *previewInstance;		
		ScreenLabel *previewLabel;							
		Entity *previewEntity;
		ScreenParticleEmitter *previewEmitter;
							
		ScreenSound *previewSound;
		ScreenSprite *previewSprite;
											
		ScreenMesh *grid;

		bool firstResize;
		
		bool firstMove;

		int placementCount;
	
		
		Number previewAspectRatio;

		bool placing;
		bool moving;
		bool scalingY;
		bool scalingX;		
		bool rotating;
		bool panning;
		bool zooming;
		bool zoomingMoved;
		
		bool parenting;
		Entity *parentingChild;
		ScreenLine *parentingLine;
		
		
		int lastMode;
		
		Vector2 basePanPosition;
		Vector2 zoomBasePosition;
		Vector2 zoomBaseMousePosition;
		Vector2 baseScaleScreenPosition;
				
		Number baseZoomScale;
		
		Number baseRotateAngle;
		
		int selectedEntityPositionMode;
		
		Vector3 baseScale;
		
		Vector2 mouseBase;
		std::vector<Vector2> baseEntityPositions;
		std::vector<Vector2> baseEntityScales;
		std::vector<Number> baseRotateAngles;
		Vector2 groupCenterPoint;
		Number groupRoll;
		Number baseAngle;
	
		ScreenShape *placingShape;	
		Vector2 placingAnchor;
		
		ScreenShape *screenPreviewShape;
		ScreenShape *sizePreviewShape;
				
		Vector2 dragOffset;
		bool isDraggingEntity;
		bool isScalingEntity;
		

		
		Entity *screenTransform;
		ScreenShape *screenTransformShape;
		ScreenImage *transformRotator;

		ScreenImage *transformScalerY;
		ScreenImage *transformScalerX;		
		ScreenImage *transformScalerXY;
							
		ScreenImage *centerImage;
		
		Entity *properties;
		ScreenShape *propertiesBg;

		Entity *viewOptions;
		ScreenShape *viewOptionsBg;
		
		UITextInput *gridSizeInput;
		UICheckBox *gridCheckBox;
		
		UICheckBox *pixelSnapBox;
		UICheckBox *gridSnapBox;
		
		UICheckBox *showRefsBox;
		
		UITextInput *scaleInput;
		
		Entity *toolPalette;
		ScreenShape *toolPaletteBg;
		
		UIImageButton *arrowToolButton;
		UIImageButton *shapeToolButton;
		UIImageButton *zoomToolButton;
		UIImageButton *panToolButton;
		UIImageButton *imageToolButton;
		UIImageButton *textToolButton;
		UIImageButton *parentToolButton;
		UIImageButton *entityToolButton;
		UIImageButton *soundToolButton;
		UIImageButton *spriteToolButton;
		UIImageButton *particlesToolButton;
				
		UIImageButton *linkToolButton;
						
		UIComboBox *aspectComboBox;
		UIComboBox *zoomComboBox;
		
		UIButton *moveUpButton;
		UIButton *moveDownButton;
		UIButton *moveTopButton;
		UIButton *moveBottomButton;
		UIButton *unparentButton;
								
		Number zooms[16];
						
		Number aspects[16];
				
		ScreenImage *selectorImage;
		int mode;	
};

class EntityClipboardData {
	public:
		EntityClipboardData(){}
		
		std::vector<Entity*> entities;
};

class PolycodeEntityEditor : public PolycodeEditor {
	public:
		PolycodeEntityEditor();
		virtual ~PolycodeEntityEditor();
	
		bool openFile(OSFileEntry filePath);
		void Resize(int x, int y);
		
		String Copy(void **data);
		void Paste(void *data, String clipboardType);
		void destroyClipboardData(void *data, String type);

		void Activate();		
		
		void saveCurveToObject(ObjectEntry *entry, BezierCurve *curve);
		void saveEntityToObjectEntry(Entity *entity, ObjectEntry *entry);
		void saveFile();
		
		void doAction(String actionName, PolycodeEditorActionData *data);
					
		void handleDroppedFile(OSFileEntry file, Number x, Number y);

		void handleEvent(Event *event);

	protected:

		UIHSizer *mainSizer;
		PropertiesSizer *propSizer;
		EntityTreeView *treeView;
		PolycodeEntityEditorMain *editorMain;
};

