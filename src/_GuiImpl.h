#ifdef CSPRITE_MAIN_CPP // Ensures that it's only included by main.cpp

/*
	File: _GuiImpl.h
		- These Are The Inline functions for gui.
		- any new window is basically a function.
		- everything should be "static inline" so it basically get's substituted.
		- this file has access to all the global variables, functions etc of "main.cpp"
		- it is separated to a file for "clean" code.
		- it is recommended to not create a global variable in this file itself
*/

static inline void _GuiMenuWindow() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("New", "Ctrl+N")) {
				ShowNewCanvasWindow = 1;
				CanvasFreeze = true;
			}
			if (ImGui::MenuItem("Open", "Ctrl+O")) {
				char *filePath = tinyfd_openFileDialog("Open A File", NULL, NumOfFilterPatterns, FileFilterPatterns, "Image File (.png, .jpg, .jpeg)", 0);
				if (filePath != NULL) {
					if (LoadImageToCanvas(filePath, &CanvasDims[0], &CanvasDims[1], &CanvasData) == 0) {
						_FreeNSaveHistory();
						if (UpdateTextures() != 0)
							GuiErrorOccured = -1;

						GenCanvasBgTex();
						UpdateCanvasRect();
						FilePath = std::string(filePath);
						SDL_SetWindowTitle(window, WINDOW_TITLE_CSTR);
					}
				}
			}
			if (ImGui::BeginMenu("Save")) {
				if (ImGui::MenuItem("Save", "Ctrl+S")) {
					FilePath = FixFileExtension(FilePath);
					SaveImageFromCanvas(FilePath);
					SDL_SetWindowTitle(window, WINDOW_TITLE_CSTR);
					FreeHistory(&CurrentState);
					SaveHistory(&CurrentState, CANVAS_SIZE_B, CanvasData);
				}
				if (ImGui::MenuItem("Save As", "Alt+S")) {
					char *filePath = tinyfd_saveFileDialog("Save A File", NULL, NumOfFilterPatterns, FileFilterPatterns, "Image File (.png, .jpg, .jpeg)");
					if (filePath != NULL) {
						FilePath = FixFileExtension(std::string(filePath));
						SaveImageFromCanvas(FilePath);
						SDL_SetWindowTitle(window, WINDOW_TITLE_CSTR);
						FreeHistory(&CurrentState);
						SaveHistory(&CurrentState, CANVAS_SIZE_B, CanvasData);
					}
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit")) {
			if (ImGui::MenuItem("Undo", "Ctrl+Z")) {
				HISTORY_UNDO(CurrentState, CANVAS_SIZE_B, CanvasData);
			}
			if (ImGui::MenuItem("Redo", "Ctrl+Y")) {
				HISTORY_REDO(CurrentState, CANVAS_SIZE_B, CanvasData);
			}
			if (ImGui::MenuItem("Preferences")) {
				ShowSettingsWindow = true;
				CanvasFreeze = true;
			}

			if (ImGui::BeginMenu("Palette")) {
				for (unsigned int i = 0; i < P_Arr->numOfEntries; ++i) {
					if (ImGui::MenuItem(P_Arr->entries[i]->name, NULL)) {
						PaletteIndex = i;
					}
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("About")) {
				OpenURL("https://github.com/pegvin/CSprite/wiki/About-CSprite");
			}
			if (ImGui::MenuItem("GitHub")) {
				OpenURL("https://github.com/pegvin/CSprite");
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

static inline void _GuiSettingsWindow() {
	if (ImGui::BeginPopupModal(
			"Settings###ShowSettingsWindow",
			NULL,
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize   |
			ImGuiWindowFlags_NoMove
	)) {
		ImGui::SetWindowSize({275.0f, 165.0f}, 0);

		static bool vsync = AppSettings->vsync;
		static bool custom_cursor = AppSettings->CustomCursor;
		static bool accel = AppSettings->accelerated;
		static int currItemIdx = 0;
		static const char* rendererList[5] = { "OpenGL", "Vulkan", "Metal", "Direct3D", "Software" };
		ImGui::Checkbox("VSync", &vsync);
		ImGui::Checkbox("Custom Curspr", &custom_cursor);
		ImGui::Checkbox("Hardware accelerated", &accel);
		ImGui::Combo("Renderer", &currItemIdx, rendererList, 5, -1);

		if (ImGui::Button("Save")) {
			AppSettings->vsync = vsync;
			AppSettings->CustomCursor = custom_cursor;
			AppSettings->accelerated = accel;
			strncpy(AppSettings->renderer, rendererList[currItemIdx], 128);
			WriteSettings(AppSettings);
			VirtualMouseInit(renderer);

			CanvasFreeze = false;
			ShowSettingsWindow = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) {
			CanvasFreeze = false;
			ShowSettingsWindow = false;
		}
		ImGui::EndPopup();
	} else {
		ImGui::OpenPopup("Settings###ShowSettingsWindow");
	}
}

static inline void _GuiNewCanvasWindow() {
	if (ImGui::BeginPopupModal(
			"New Canvas###ShowNewCanvasWindow",
			NULL,
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize   |
			ImGuiWindowFlags_NoMove
	)) {
		static int NEW_DIMS[2] = {60, 40};
		ImGui::SetWindowSize({240.0f, 115.0f}, 0);
		ImGui::InputInt("width", &NEW_DIMS[0], 1, 1, 0);
		ImGui::InputInt("height", &NEW_DIMS[1], 1, 1, 0);

		if (ImGui::Button("Ok")) {
			FreeHistory(&CurrentState);
			CanvasDims[0] = NEW_DIMS[0];
			CanvasDims[1] = NEW_DIMS[1];
			GenCanvasBuff();
			GenCanvasBgTex();
			UpdateTextures();
			UpdateCanvasRect();
			SaveHistory(&CurrentState, CANVAS_SIZE_B, CanvasData);
			CanvasFreeze = false;
			ShowNewCanvasWindow = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) {
			CanvasFreeze = false;
			ShowNewCanvasWindow = false;
		}
		ImGui::EndPopup();
	} else {
		ImGui::OpenPopup("New Canvas###ShowNewCanvasWindow");
	}
}

static inline void _GuiPaletteWindow() {
	if (ImGui::Begin("PWindow", NULL, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
		ImGui::SetWindowSize({70.0f, (float)WindowDims[1]});
		ImGui::SetWindowPos({0.0f, 25.0f});
		for (unsigned int i = 0; i < P->numOfEntries; i++) {
			ImGuiDrawList = ImGui::GetWindowDrawList();
			if (i != 0 && i % 2 != 0)
				ImGui::SameLine();

			if (ImGui::ColorButton(ColorIndex == i ? "Selected Color" : ("Color##" + std::to_string(i)).c_str(), {(float)((P->entries[i] >> 24) & 0xFF)/255, (float)((P->entries[i] >> 16) & 0xFF)/255, (float)((P->entries[i] >> 8) & 0xFF)/255, (float)(P->entries[i] & 0xFF)/255}))
				ColorIndex = i;

			if (ColorIndex == i)
				ImGuiDrawList->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), 0xFFFFFFFF, 0, 0, 1);
		};
		ImGui::End();
	}
}

static inline void _GuiTextWindow() {
	if (ImGui::Begin("ToolAndZoomWindow", NULL, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |  ImGuiWindowFlags_NoFocusOnAppearing)) {
		ImGui::SetWindowPos({0.0f, (float)(WindowDims[1] - 55)});
		std::string selectedToolText;

		switch (Tool) {
			case BRUSH:
				if (Mode == SQUARE)
					selectedToolText = "Square Brush - (Size: " + std::to_string(BrushSize) + ")";
				else
					selectedToolText = "Circle Brush - (Size: " + std::to_string(BrushSize) + ")";
				break;
			case ERASER:
				if (Mode == SQUARE)
					selectedToolText = "Square Eraser - (Size: " + std::to_string(BrushSize) + ")";
				else
					selectedToolText = "Circle Eraser - (Size: " + std::to_string(BrushSize) + ")";
				break;
			case FILL:
				selectedToolText = "Fill";
				break;
			case INK_DROPPER:
				selectedToolText = "Ink Dropper";
				break;
			case PAN:
				selectedToolText = "Panning";
				break;
			case LINE:
				if (Mode == SQUARE)
					selectedToolText = "Square Line - (Size: " + std::to_string(BrushSize) + ")";
				else
					selectedToolText = "Round Line - (Size: " + std::to_string(BrushSize) + ")";
				break;
			case RECTANGLE:
				if (Mode == SQUARE)
					selectedToolText = "Square Rect - (Size: " + std::to_string(BrushSize) + ")";
				else
					selectedToolText = "Round Rect - (Size: " + std::to_string(BrushSize) + ")";
				break;
			case RECT_SELECT:
				selectedToolText = "Rectangle Selection";
				break;
			case CIRCLE_TOOL:
				selectedToolText = "Circle - (Border Size: " + std::to_string(BrushSize) + ")";
				break;
			}

		ImVec2 textSize1 = ImGui::CalcTextSize(selectedToolText.c_str(), NULL, false, -2.0f);
		ImVec2 textSize2 = ImGui::CalcTextSize(ZoomText.c_str(), NULL, false, -2.0f);
		ImGui::SetWindowSize({(float)(textSize1.x + textSize2.x), (float)(textSize1.y + textSize2.y) * 2}); // Make Sure Text is visible everytime.

		ImGui::Text("%s", selectedToolText.c_str());
		ImGui::Text("%s", ZoomText.c_str());
		ImGui::End();
	}
}

#endif // CSPRITE_MAIN_CPP
