// SOM.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#include <iostream>
#include <fstream>
#include <time.h>

#include "DataSet.h"
#include "CSOMLattice.h"
#include "CSOM2DLatticeTopology.h"
#include "CSOMCellDoubleFactory.h"
#include "CSOMTorusLatticeTopology.h"
#include "CSOM3DLatticeTopology.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

CSOMLattice * pSOM=0;
HWND temphWnd;

void StartSOM();

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SOM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_SOM);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_SOM);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_SOM;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   temphWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent, x,y;
	HDC hdc;
	vector<double> Weights;

	//these hold the dimensions of the client window area
	static int cxClient, cyClient; 

	//used to create the back buffer
	static HDC   hdcBackBuffer;
	static HBITMAP hBitmap;
	static HBITMAP hOldBitmap;

	HPEN OldPen, pen;
	
	switch (message) 
	{
		case WM_CREATE:
			//to get get the size of the client window first we need  to create
			 //a RECT and then ask Windows to fill in our RECT structure with
			 //the client window size. Then we assign to cxClient and cyClient 
			 //accordingly
			 RECT rect;

			 GetClientRect(hWnd, &rect);

			 cxClient = rect.right;
			 cyClient = rect.bottom;

			  //create a memory device context
			 hdcBackBuffer = CreateCompatibleDC(NULL);

			 //get the DC for the front buffer
			 hdc = GetDC(hWnd);

			 hBitmap = CreateCompatibleBitmap(hdc,
											  cxClient,
											  cyClient);

        
			 //select the bitmap into the memory device context
			 hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);

			 //don't forget to release the DC
			 ReleaseDC(hWnd, hdc); 

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;				
				  
				case ID_FILE_START:
					StartSOM();
					break;

				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			
			PAINTSTRUCT ps;
          
			BeginPaint (hWnd, &ps);

			//fill the backbuffer with white
			BitBlt(hdcBackBuffer,
					0,
					0,
					cxClient,
					cyClient,
					NULL,
					NULL,
					NULL,
					WHITENESS);
          
			pen   = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			OldPen   = (HPEN)SelectObject(hdcBackBuffer, pen);

			Rectangle(hdcBackBuffer,0.2*cxClient, 0.3*cyClient, 0.4*cxClient, 0.5*cyClient);
			Rectangle(hdcBackBuffer,0.2*cxClient, 0.6*cyClient, 0.4*cxClient, 0.8*cyClient);
			Rectangle(hdcBackBuffer,0.5*cxClient, 0.3*cyClient, 0.7*cxClient, 0.5*cyClient);
			Rectangle(hdcBackBuffer,0.5*cxClient, 0.6*cyClient, 0.7*cxClient, 0.8*cyClient);


			if (pSOM != 0) 
			{
				for (x=0; x<10; x++)
				{
					for (y=0; y<10; y++)
					{
						if (x<9 && y<9) 
						{	
							dynamic_cast<const CSOMCellDouble*>(pSOM->GetCell(x+y*10))->GetCellWeights(&Weights);
							MoveToEx(hdcBackBuffer,Weights[0]*cxClient,Weights[1]*cyClient,NULL);

							dynamic_cast<const CSOMCellDouble*>(pSOM->GetCell((x+1)+y*10))->GetCellWeights(&Weights);
							LineTo(hdcBackBuffer,Weights[0]*cxClient,Weights[1]*cyClient);

							dynamic_cast<const CSOMCellDouble*>(pSOM->GetCell((x+1)+(y+1)*10))->GetCellWeights(&Weights);
							LineTo(hdcBackBuffer,Weights[0]*cxClient,Weights[1]*cyClient);

							dynamic_cast<const CSOMCellDouble*>(pSOM->GetCell(x+(y+1)*10))->GetCellWeights(&Weights);
							LineTo(hdcBackBuffer,Weights[0]*cxClient,Weights[1]*cyClient);

							dynamic_cast<const CSOMCellDouble*>(pSOM->GetCell(x+y*10))->GetCellWeights(&Weights);
							LineTo(hdcBackBuffer,Weights[0]*cxClient,Weights[1]*cyClient);
						}
						if (x==9 && y<9) 
						{
							dynamic_cast<const CSOMCellDouble*>(pSOM->GetCell(x+y*10))->GetCellWeights(&Weights);
							MoveToEx(hdcBackBuffer,Weights[0]*cxClient,Weights[1]*cyClient,NULL);

							dynamic_cast<const CSOMCellDouble*>(pSOM->GetCell(x+(y+1)*10))->GetCellWeights(&Weights);
							LineTo(hdcBackBuffer,Weights[0]*cxClient,Weights[1]*cyClient);
						}
						if (y==9 && x<9)
						{
							dynamic_cast<const CSOMCellDouble*>(pSOM->GetCell(x+y*10))->GetCellWeights(&Weights);
							MoveToEx(hdcBackBuffer,Weights[0]*cxClient,Weights[1]*cyClient,NULL);

							dynamic_cast<const CSOMCellDouble*>(pSOM->GetCell((x+1)+y*10))->GetCellWeights(&Weights);
							LineTo(hdcBackBuffer,Weights[0]*cxClient,Weights[1]*cyClient);
						}
						
						
						dynamic_cast<const CSOMCellDouble*>(pSOM->GetCell(x+y*10))->GetCellWeights(&Weights);
						Ellipse(hdcBackBuffer,(cxClient*Weights[0])-5,(cyClient*Weights[1])-5, 
											(cxClient*Weights[0])+5,(cyClient*Weights[1])+5);

					}
				}				
			}

			SelectObject(hdcBackBuffer, OldPen);
			DeleteObject(pen);

			//now blit the backbuffer to the front
			BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY); 
          
			EndPaint (hWnd, &ps);
			
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

void StartSOM()
{	
	ofstream SOMlog("C:\\temp\\SOMlog.txt");
//	ofstream SOMout("C:\\temp\\TrainedXSOM.csv");

	long i,  seed;		

	//seed the random number generator
	seed = static_cast<long>(time( NULL ) );
	srand( seed );
	SOMlog << "Seed: " << seed << endl;

	//get the dataset going
	DataSet SOMData;
//	DataSet TrainedSOM;

	SOMlog << "Begin LoadDataset" << endl;
	SOMlog.flush();
	SOMData.LoadDataSet("c:\\temp\\Random4.csv");
//	TrainedSOM.LoadDataSet("c:\\temp\\TrainedSOM_2D_50x50.csv", numObs, numDes);
	
	//create 2D topology
	SOMlog << "Begin Create topology obj" << endl;
	SOMlog.flush();
	CSOM2DLatticeTopology SOMTopology(10,10);

	//create a factory
	SOMlog << "Begin create factory" << endl;
	SOMlog.flush();
//	CSOMCellDoubleFactory CellFactory(&TrainedSOM);
	CSOMCellDoubleFactory CellFactory(&SOMData);

	//set the settings
	CSOMLatticeSettings SOMSettings;	//make a settings object
	SOMSettings.CellFactory (&CellFactory);	//set the factory
	SOMSettings.LatticeTopology( dynamic_cast<ISOMLatticeTopology *>(&SOMTopology)); //set the topology obj.
	SOMSettings.InitMethod( SOMLatticeSettings::SOMInit_Random);	//set the data initialization sampling method
	SOMSettings.TotalIterations(10000);	//set the total number of training sampling iterations
	SOMSettings.TrainingStepSize(5);	//set the number of steps to take before allowing an update

	//create a lattice using the above settings
	SOMlog << "Begin create lattice" << endl;
	SOMlog.flush();
	CSOMLattice SOM(&SOMSettings);
	pSOM = &SOM;  //set the global for drawing purposes

	SOMlog << "Begin training" << endl;
	SOMlog.flush();

	i=0;  //iteration counter for logging
	InvalidateRect(temphWnd, NULL, TRUE);
	UpdateWindow(temphWnd);

	//train it
	while (SOM.Train()) //when it runs out of iterations, it will return false
	{
		i+=500;
		Sleep(0);  //used to delay the drawing
		SOMlog << "Iteration: " << i << endl;//The SOM will return true once every TrainingStepSize iterations for visual updates etc.
		SOMlog.flush();	
		//this will call WM_PAINT which will render the map
		InvalidateRect(temphWnd, NULL, FALSE);
		UpdateWindow(temphWnd);
	};

	pSOM = 0;  //reset the global pointer to null

	//persist the trained SOM
//	const CSOMCellDouble * tempCell;
//	vector<double> weights;

	//write out the cell weights to preserve the trained SOM
//	SOMout << "Descr1,Descr2" << endl;

	//step through each cell and write out the weights
	//if I set this as the data set to use for a factory object, and specify
	//SOMInit_DataSequential as the InitMethod in the settings object, 
	//I can recreate the saved SOM for later use
//	for (i=0; i<SOM.CellCount(); i++)
//	{
//		tempCell = dynamic_cast<const CSOMCellDouble *>(SOM.GetCell(i));
//		tempCell->GetCellWeights(&weights);

//		for (j=0; j<weights.size(); j++)
//		{
//			SOMout << weights[j];
//			if (j<weights.size()-1)
//				SOMout << ",";
//		}
//		SOMout << endl;
//	}	
}




