#include <QtTest>
#include <QString>
#include "labyrinthmodel.h"
#include "labyrinthloadmock.h"
// add necessary includes here

class LabyrinthModelTest : public QObject
{
    Q_OBJECT

private:
    labyrinthModel* _model;
    LabyrinthLoad* _labyrinthLoad;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testCalculateVisibility();
    void testMoveUp();
    void testMoveDown();
    void testMoveLeft();
    void testCheckFinish();

};

// tesztkörnyezet inicializálása
void LabyrinthModelTest::initTestCase()
{
    _labyrinthLoad = new LabyrinthLoadMock();
    _model = new labyrinthModel();
}

// tesztkörnyezet megsemmisítése
void LabyrinthModelTest::cleanupTestCase()
{
    delete _labyrinthLoad;
    delete _model;
}

// tesztesetek
void LabyrinthModelTest::testCalculateVisibility()
{
    _model->calculateVisibility("easy");

    // ellenőrizzük, hogy a játékos a megfelelő mezőn áll
    QCOMPARE(_model->player(), 380);
    // ellenőrizzük a látható mezők számát
    QCOMPARE(_model->visiblePlatforms().size(), 6);
}

void LabyrinthModelTest::testMoveUp()
{
    // alaphelyzet ellenőrzés
    QCOMPARE(_model->player(), 380);
    _model->moveUp();
    // mozgás ellenőrzése
    QCOMPARE(_model->player(), 360);
}

void LabyrinthModelTest::testMoveDown()
{
    // alaphelyzet ellenőrzés
    QCOMPARE(_model->player(), 360);
    _model->moveDown();
    // mozgás ellenőrzése
    QCOMPARE(_model->player(), 380);
}

void LabyrinthModelTest::testMoveLeft()
{
    // alaphelyzet ellenőrzés
    QCOMPARE(_model->player(), 380);
    _model->moveLeft();
    // mozgás ellenőrzése (nem tudot ebbe az irányba mozogni)
    QCOMPARE(_model->player(), 380);
}

void LabyrinthModelTest::testCheckFinish()
{
    // ellenőrizzük, hogy a játékos még nem érte el a célt
    QCOMPARE(_model->checkFinish(), false);
}


QTEST_APPLESS_MAIN(LabyrinthModelTest)

#include "tst_labyrinthmodeltest.moc"
