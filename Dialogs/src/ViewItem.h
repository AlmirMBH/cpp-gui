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

class DIALOGS_LIB_API ViewItem : public gui::View
{
    enum class NamingType {GENERAL_ITEM = 1, DRINK, MEAT, FRUITVEG};

protected:
    gui::Label _lblID;
    gui::NumericEdit _id;
    gui::Label _lblName;
    gui::LineEdit _name;
    gui::Label _lblVat;
    gui::DBComboBox _vat;
    gui::Label _lblUnit;
    gui::DBComboBox _unit;
    gui::Label _lblPrice;
    gui::NumericEdit _Price;

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
    dp::IDataSet* _pDS = nullptr;
    td::INT4 _paramFrom;
    td::INT4 _paramTo;

    std::vector<td::INT4> _itemsToDelete, _itemsToInsert, _itemsToUpdate;

public:
    ViewItem();
    ~ViewItem();

protected:
    void populateData();
    bool loadComboBox(td::String select, gui::DBComboBox& combo);
    virtual bool onChangedSelection(gui::TableEdit* pTE);
    void populateDSRow(dp::IDataSet::Row& row);
    bool canAdd();
    td::INT4 getIDfromTable(int rowID);
    bool canUpdate(int iRow);
    bool itemExistsInTransactions(td::INT4 id);
    bool canDelete(int iRow);
    bool eraseNamings(NamingType nt);
    bool eraseItems();
    bool insertNamings(NamingType nt);
    bool insertItems();
    bool updateItems();
    bool saveData();
    virtual bool onClick(gui::Button* pBtn);
};
