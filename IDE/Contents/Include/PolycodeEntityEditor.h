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
		virtual ~PolycodeEntityEditorActionData() {}

		std::vector<PolycodeEntityEditorActionDataEntry> enties;
		PolycodeEntityEditorActionDataEntry entry;
		bool reverse;
}

class EntityTreeView : public UIElement {
	public:
		EntityTreeView(Entity *rootEntry);
		~EntityTreeView();

		void Resize(Number width, Number height);
		void handleEvent(Event *event);

		void syncNodeToEntity(UITree *node, Entity *entity);

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
}

class PropertiesSizer : public UIElement {
	public:
		PropertiesSizer();
		~PropertiesSizer();

		void Resize(Number width, Number height);

		UIVSizer *sizer;
}


class EntityNameDisplay : public ScreenEntity {
	public:
		EntityNameDisplay(Entity *targetEntity);
		~EntityNameDisplay();

		void Update();

		ScreenLabel *label;
		ScreenLabel *tagsLabel;
		Entity *targetEntity;
}

class PolycodeEntityEditorMain : public UIElement {
	public:
		PolycodeEntityEditorMain(PolycodeEditor *editor);
		virtual ~PolycodeScreenEditorMain();

		void Resize(Number width, Number height);
		virtual void syncTransformToSelected();
		Entity *addNewLayer(String layerName);
		void updateCursor();
		virtual void selectEntity(Entity *entity, bool doAction = true); 	// Perhaps make this one non-virtual and add an onSelect callback
		virtual void resetSelectedEntityTransforms() = 0;
		void setMode(int newMode);
		virtual void handleEvent(Event *event);
		void resizePreviewScreen();
		void handleDroppedFile(OSFileEntry file, Number x, Number y);
		bool hasSelected(Entity *entity);
		
		void deleteEntity(Entity *entity);
		
		void applyEditorOnly(Entity *entity);
		void applyEditorOnlyChildren(Entity *entity);
		virtual void applyEditorProperties(ScreenEntity *entity);

		

}
