#pragma once
#include "ViewItem.h"
#include <iostream>

    /**
     * Debugging function to print terminal logs
     */
    template <typename T>
    void printOutput(const std::string message = "Default message", T x = 0) {
        std::cout << message << x << std::endl;
    }

    ViewItem::ViewItem()
        : _lblID(tr("ID:"))
        , _id(td::int4)
        , _lblName(tr("Name:"))
        , _lblVat(tr("VAT:"))
        , _vat(td::int4)
        , _lblUnit(tr("Unit:"))
        , _unit(td::int4)
        , _lblFromID(tr("From ID:"))
        , _fromID(td::int4)
        , _lblPrice(tr("Default price: "))
        , _Price(td::real8)
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
        , _gl(5, 6)
        , _db(dp::getMainDatabase())
        , _paramFrom(0)
        , _paramTo(100)
    {
        _fromID.setValue(_paramFrom);
        _toID.setValue(_paramTo);

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
        gc.appendRow(_lblID);
        gc.appendCol(_id);
        gc.appendCol(_lblName);
        gc.appendCol(_name, 0);

        gc.appendRow(_lblVat, td::HAlignment::Left, td::VAlignment::Center);
        gc.appendCol(_vat, td::HAlignment::Left, td::VAlignment::Center);
        gc.appendCol(_lblUnit, td::HAlignment::Left, td::VAlignment::Center);
        gc.appendCol(_unit, td::HAlignment::Left, td::VAlignment::Center);
        gc.appendCol(_lblPrice, td::HAlignment::Left, td::VAlignment::Center);
        gc.appendCol(_Price, td::HAlignment::Left, td::VAlignment::Center);

        gc.appendRow(_table, 0);
        gc.appendRow(_hlBtns, 0);

        gui::View::setLayout(&_gl);

        populateData();
        loadComboBox("select ID, Name from VAT", _vat);
        loadComboBox("select ID, Name from Unit", _unit);
    }


    ViewItem::~ViewItem()
    {
        if (_pDS)
            _pDS->release();
    }


    void ViewItem::populateData()
    {
        _pDS = _db->createDataSet("select n.ID, n.Name, n.Price as ItemPrice, a.VATID, a.UnitID, b.Name as VATName, c.Name as UnitName"
            " from Naming n, Item a, VAT b, Unit c where n.TipID = 1 and n.TipID = a.TypeID and n.ID = a.ID and a.VATID = b.ID and a.UnitID = c.ID and n.ID >= ? and n.ID <= ? "
            , dp::IDataSet::Execution::EX_MULT);
        dp::Params params(_pDS->allocParams());
        params << _paramFrom << _paramTo;

        dp::DSColumns cols(_pDS->allocBindColumns(7));
        cols << "ID" << td::int4 << "Name" << td::string8 << "VATID" << td::int4 << "UnitID" << td::int4
            << "VATName" << td::string8 << "UnitName" << td::string8 << "ItemPrice" << td::real8;

        if (!_pDS->execute())
        {
            _pDS = nullptr;
            return;
        }

        _table.init(_pDS, { 0, 1, 4, 5, 6});
    }

    bool ViewItem::loadComboBox(td::String select, gui::DBComboBox& combo)
    {
        dp::IStatementPtr pSelect = _db->createStatement(select.c_str());
        dp::Columns pCols = pSelect->allocBindColumns(2);
        td::String name;
        td::INT4 id;
        pCols << "ID" << id << "Name" << name;

        if (!pSelect->execute())
            return false;

        while (pSelect->moveNext())
        {
            combo.addItem(name, id);
        }

        combo.selectIndex(0);
        return true;
    }

    bool ViewItem::onChangedSelection(gui::TableEdit* pTE)
    {
        if (pTE == &_table)
        {
            int iRow = _table.getFirstSelectedRow();
            if (iRow < 0)
            {
                _id.toZero();
                _name.toZero();
                _vat.toZero();
                _unit.toZero();
                _Price.toZero();
                return true;
            }
            dp::IDataSet* pDS = _table.getDataSet();
            auto& row = pDS->getRow(iRow);
            _id.setValue(row[0]);
            _name.setValue(row[1]);
            _vat.setValue(row[2].i4Val());
            _unit.setValue(row[3].i4Val());
            _Price.setValue(row[6].r8Val());
            return true;
        }

        return false;
    }

    void ViewItem::populateDSRow(dp::IDataSet::Row& row)
    {
        td::Variant val;
        _id.getValue(val);
        row[0].setValue(val);
        _name.getValue(val);
        row[1].setValue(val);
        _vat.getValue(val);
        row[2].setValue(val);
        _unit.getValue(val);
        row[3].setValue(val);
        row[4].setValue(_vat.getSelectedText());
        row[5].setValue(_unit.getSelectedText());
        _Price.getValue(val);
        row[6].setValue(val);
    }


    bool ViewItem::canAdd()
    {
        td::Variant id = _id.getValue();
        dp::IDataSet* pDS = _table.getDataSet();

        for (size_t i = 0; i < pDS->getNumberOfRows(); ++i)
        {
            auto& row = pDS->getRow(i);

            if (row[0] == id)
            {
                return false;
            }
        }

        return true;
    }


    td::INT4 ViewItem::getIDfromTable(int rowID)
    {
        dp::IDataSet* pDS = _table.getDataSet();
        auto& row = pDS->getRow(rowID);
        return row[0].i4Val();
    }


    bool ViewItem::canUpdate(int iRow)
    {
        td::Variant id = _id.getValue();
        td::INT4 idTable = getIDfromTable(iRow);

        if (idTable == id.i4Val())
        {
            return true;
        }

        return false;
    }


    bool ViewItem::itemExistsInTransactions(td::INT4 id)
    {
        NamingType nt = NamingType::GENERAL_ITEM;
        dp::IStatementPtr pSel(_db->createStatement("select count(1) as Cnt from TransItems a where a.ItemTypeID = ? and a.ItemID = ?"));
        dp::Params pParams(pSel->allocParams());
        pParams << nt << id;
        dp::Columns pCols = pSel->allocBindColumns(1);
        td::INT4 cnt;
        pCols << "Cnt" << cnt;
        
        if (!pSel->execute())
        {
            return false;
        }
        
        pSel->moveNext();
        return (cnt > 0);
    }


    bool ViewItem::canDelete(int iRow)
    {
        return !itemExistsInTransactions(getIDfromTable(iRow));
    }


    bool ViewItem::eraseNamings(NamingType nt)
    {
        dp::IStatementPtr pDeleteNaming(_db->createStatement("delete from Naming where TipID = ? and ID = ?"));
        dp::Params pParams1(pDeleteNaming->allocParams());
        td::INT4 id;
        pParams1 << nt << id;

        for (auto item : _itemsToDelete)
        {
            id = item;

            if (!pDeleteNaming->execute())
            {
                return false;
            }
        }

        return true;
    }

    bool ViewItem::eraseItems()
    {
        NamingType type = NamingType::GENERAL_ITEM;
        td::INT4 id;
        dp::IStatementPtr pDeleteItem(_db->createStatement("delete from Item where TypeID = ? and ID = ?"));
        dp::Params pParams2(pDeleteItem->allocParams());
        pParams2 << type << id;

        for (auto item : _itemsToDelete)
        {
            id = item;
            if (!pDeleteItem->execute())
            {
                return false;
            }
        }
        return true;
    }


    bool ViewItem::insertNamings(NamingType nt)
    {
        dp::IStatementPtr pInsertNaming(_db->createStatement("insert into Naming(TipID, ID, Name, Price) values(?,?,?)"));
        dp::Params pParams(pInsertNaming->allocParams());
        td::INT4 id;
        td::String name;
        double price;
        pParams << nt << id << dp::toNCh(name, 100);

        dp::IDataSet* pDS = _table.getDataSet();
        auto rowCnt = pDS->getNumberOfRows();

        for (size_t iRow = 0; iRow < rowCnt; ++iRow)
        {
            auto& row = pDS->getRow(iRow);
            id = row[0].i4Val();
            price = row[6].r8Val();

            if (std::find(_itemsToInsert.begin(), _itemsToInsert.end(), id) == _itemsToInsert.end())
            {
                continue;
            }

            name = row[1];

            if (!pInsertNaming->execute())
            {
                return false;
            }
        }

        return true;
    }


    bool ViewItem::insertItems()
    {
        NamingType nt = NamingType::GENERAL_ITEM;

        dp::IStatementPtr pInsertItem(_db->createStatement("insert into Item(TypeID, ID, VATID, UnitID) values(?,?,?,?)"));
        dp::Params pParams2(pInsertItem->allocParams());
        td::INT4 id, idVat, idUnit;        
        pParams2 << nt << id << idVat << idUnit;

        dp::IDataSet* pDS = _table.getDataSet();
        auto rowCnt = pDS->getNumberOfRows();

        for (size_t iRow = 0; iRow < rowCnt; ++iRow)
        {
            auto& row = pDS->getRow(iRow);
            id = row[0].i4Val();

            if (std::find(_itemsToInsert.begin(), _itemsToInsert.end(), id) == _itemsToInsert.end())
            {
                continue;
            }

            idVat = row[2].i4Val();
            idUnit = row[3].i4Val();

            if (!pInsertItem->execute())
            {
                return false;
            }
        }

        return true;
    }


    bool ViewItem::updateItems()
    {
        NamingType nt = NamingType::GENERAL_ITEM;
        td::String name;
        td::INT4 id, idVat, idUnit;
        dp::IStatementPtr pChangeNaming(_db->createStatement("update Naming set Name=? where TipID=? and ID=?"));
        dp::Params pParams(pChangeNaming->allocParams());
        pParams << dp::toNCh(name, 100) << nt << id;

        dp::IStatementPtr pChangeItem(_db->createStatement("update Item set VATID=?, UnitID=? where TypeID=? and ID=?"));
        dp::Params pParams2(pChangeItem->allocParams());
        pParams2 << idVat << idUnit << nt << id;

        dp::IDataSet* pDS = _table.getDataSet();
        auto rowCnt = pDS->getNumberOfRows();

        for (size_t iRow = 0; iRow < rowCnt; ++iRow)
        {
            auto& row = pDS->getRow(iRow);
            id = row[0].i4Val();

            if (std::find(_itemsToUpdate.begin(), _itemsToUpdate.end(), id) == _itemsToUpdate.end())
            {
                continue;
            }

            name = row[1];
            idVat = row[2].i4Val();
            idUnit = row[3].i4Val();

            if (!pChangeNaming->execute())
            {
                return false;
            }

            if (!pChangeItem->execute())
            {
                return false;
            }
        }

        return true;
    }

    bool ViewItem::saveData()
    {
        dp::Transaction tr(_db);

        if (!eraseItems()) return false;
        if (!eraseNamings(NamingType::GENERAL_ITEM)) return false;
        if (!insertNamings(NamingType::GENERAL_ITEM)) return false;
        if (!insertItems()) return false;
        if (!updateItems()) return false;

        if (tr.commit())
        {
            _itemsToDelete.clear();
            _itemsToInsert.clear();
            _itemsToUpdate.clear();
        }

        return true;
    }

    bool ViewItem::onClick(gui::Button* pBtn)
    {
        if (pBtn == &_btnReload)
        {
            _paramFrom = _fromID.getValue().i4Val();
            _paramTo = _toID.getValue().i4Val();
            _table.reload();
            _itemsToDelete.clear();
            _itemsToInsert.clear();
            _itemsToUpdate.clear();
            return true;
        }

        if (pBtn == &_btnDelete)
        {
            int iRow = _table.getFirstSelectedRow();

            if (iRow < 0) return true;
            if (!canDelete(iRow)) return true;

            td::INT4 itemid = getIDfromTable(iRow);

            _table.beginUpdate();
            _table.removeRow(iRow);
            _table.endUpdate();
            _itemsToDelete.push_back(itemid);
            //if we delete an item, if it was added earlier or modified existing, and we did not save into database, remove it from these two vectors
            _itemsToInsert.erase(std::remove(_itemsToInsert.begin(), _itemsToInsert.end(), itemid), _itemsToInsert.end());
            _itemsToUpdate.erase(std::remove(_itemsToUpdate.begin(), _itemsToUpdate.end(), itemid), _itemsToUpdate.end());
            return true;
        }

        if (pBtn == &_btnUpdate)
        {
            int iRow = _table.getFirstSelectedRow();

            if (iRow < 0) return true;
            if (!canUpdate(iRow)) return true;
            
            td::INT4 itemid = getIDfromTable(iRow);

            _table.beginUpdate();
            auto& row = _table.getCurrentRow();
            populateDSRow(row);
            _table.updateRow(iRow);
            _table.endUpdate();

            //update database only if an item is not new
            if (std::find(_itemsToInsert.begin(), _itemsToInsert.end(), itemid) == _itemsToInsert.end())
            {
                _itemsToUpdate.push_back(itemid);
            }

            return true;
        }

        if (pBtn == &_btnInsert)
        {
            int iRow = _table.getFirstSelectedRow();

            if (iRow < 0) iRow = 0;
            if (!canAdd()) return true;
            
            td::INT4 itemid = getIDfromTable(iRow);

            _table.beginUpdate();
            auto& row = _table.getEmptyRow();
            populateDSRow(row);
            _table.insertRow(iRow);
            _table.endUpdate();

            _itemsToUpdate.erase(std::remove(_itemsToUpdate.begin(), _itemsToUpdate.end(), itemid), _itemsToUpdate.end());
            _itemsToInsert.push_back(itemid);
            //do not remove from _itemsToDelete, maybe we deleted an item with ID (itemid), and now we add different item with same ID 
            return true;
        }

        if (pBtn == &_btnPushBack)
        {
            td::INT4 itemid = _id.getValue().i4Val();

            if (!canAdd()) return true;

            _table.beginUpdate();
            auto& row = _table.getEmptyRow();
            populateDSRow(row);
            _table.push_back();
            _table.endUpdate();

            _itemsToUpdate.erase(std::remove(_itemsToUpdate.begin(), _itemsToUpdate.end(), itemid), _itemsToUpdate.end());
            _itemsToInsert.push_back(itemid);
            //do not remove from _itemsToDelete, maybe we deleted an item with ID (itemid), and now we add different item with same ID 
            return true;
        }

        if (pBtn == &_btnSave)
        {
            saveData();
            return true;
        }

        return false;
    }
