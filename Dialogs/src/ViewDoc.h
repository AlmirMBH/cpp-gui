#pragma once
#include <gui/View.h>
#include <gui/Label.h>
#include <gui/LineEdit.h>
#include <gui/TextEdit.h>
#include <gui/VerticalLayout.h>
#include <gui/HorizontalLayout.h>
#include <gui/GridLayout.h>
#include <gui/Button.h>
#include <gui/NumericEdit.h>
#include <gui/ComboBox.h>
#include <gui/DBComboBox.h>
#include <gui/CheckBox.h>
#include <gui/Slider.h>
#include <gui/ProgressIndicator.h>
#include <gui/GridComposer.h>
#include <gui/DateEdit.h>
#include <gui/TimeEdit.h>
#include <gui/ColorPicker.h>
#include <gui/TableEdit.h>
#include <dp/IDatabase.h>
#include <dp/IDataSet.h>
#include <dp/IDataSetDelegate.h>
#include <fo/FileOperations.h>
#include <gui/ImageView.h>
#include <gui/Color.h>
#include "../../common_files/include/DialogsLib.h"



class DIALOGS_LIB_API ViewDoc : public gui::View
{
protected:

    gui::Label _lblDate;
    gui::DateEdit _date;

    gui::Label _toDo;


    gui::TableEdit _table;

    gui::Label _lblFromID;
    gui::NumericEdit _fromID;
    gui::Label _lblToID;
    gui::NumericEdit _toID;

    gui::HorizontalLayout _hlBtns;
    gui::Button _btnSave;
    gui::Button _btnReload;
    gui::Button _btnRemoveAll;
    gui::Button _btnDelete;
    gui::Button _btnUpdate;
    gui::Button _btnInsert;
    gui::Button _btnPushBack;
    gui::GridLayout _gl;


    dp::IDatabase* _db;
    dp::IDataSetPtr _pDS = nullptr;
    td::INT4 _paramFrom;
    td::INT4 _paramTo;
public:
    ViewDoc()
        : _lblDate(tr("Date:"))     
        , _lblFromID(tr("From ID:"))
        , _fromID(td::int4)
        , _lblToID(tr("To ID:"))
        , _toID(td::int4)
        , _hlBtns(12)
        , _btnSave(tr("Save"), tr("SaveTT"))
        , _btnReload(tr("Reload"), tr("ReloadTT"))
        , _btnRemoveAll(tr("DelAll"), tr("DelAllTT"))
        , _btnDelete(tr("Delete"), tr("DeleteTT"))
        , _btnUpdate(tr("Update"), tr("UpdateTT"))
        , _btnInsert(tr("Insert"), tr("InsertTT"))
        , _btnPushBack(tr("PushBack"), tr("PushBackTT"))
        , _gl(4, 2)
        , _db(dp::getMainDatabase())
        , _paramFrom(0)
        , _paramTo(100)
        , _toDo("TODO: Be able to create a transaction with items in the tab above...")
    {
        _fromID.setValue(_paramFrom);
        _toID.setValue(_paramTo);

        //populate last row (horizontal layout)
        _hlBtns.append(_btnSave);
        _hlBtns.appendSpacer();
        _hlBtns.append(_lblFromID);
        _hlBtns.append(_fromID);
        _hlBtns.append(_lblToID);
        _hlBtns.append(_toID);
        _hlBtns.append(_btnReload);
        _hlBtns.appendSpace(10);
        _hlBtns.append(_btnDelete);
        _hlBtns.append(_btnUpdate);
        _hlBtns.append(_btnInsert);
        _hlBtns.append(_btnPushBack);
        _btnPushBack.setAsDefault();

        gui::GridComposer gc(_gl);
       
        gc.appendRow(_lblDate);
        gc.appendCol(_date, 0);
        gc.appendRow(_toDo, 0);
        gc.appendRow(_table, 0);
        gc.appendRow(_hlBtns, 0);

        gui::View::setLayout(&_gl);



    }
};
