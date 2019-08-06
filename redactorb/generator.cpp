#include "generator.h"


Generator::Generator(QGraphicsScene *scene,QWidget *parent) : QTextEdit(parent)
{
    myScene=scene;
    pochcod = "#include <iostream>\n"
              "#include <conio.h>\n"
              "using namespace std;\n"
              "\n"
              "int main()\n"
              "{";
    kincod = "getch();\n"
             "return 0;\n"
             "}";
    setText(pochcod);
}

QString Generator::getKod(QString s){
    QString st;
    char lapki = '"';
    if(s.left(9).contains("Вивести: ")){
      st.append("cout << ");
      st.append(lapki);
      st.append(s.right(s.length()-9));
      st.append(lapki);
      st.append(";");
    } else if (s.left(8).contains("Ввести: ")){
        st.append(s.right(s.length()-8)+"\n");
        QString neg,gotove;
        if (st.contains("String")||st.contains("string")){
            neg.append(st.right(st.length()-7));
            gotove.append(neg.left(neg.length()-1));
        } else if (st.contains("int")||st.contains("Int")){
            neg.append(st.right(st.length()-4));
            gotove.append(neg.left(neg.length()-1));
        } else if (st.contains("Double")||st.contains("double")){
            neg.append(st.right(st.length()-7));
            gotove.append(neg.left(neg.length()-1));
        } else if (st.contains("Float")||st.contains("float")){
            neg.append(st.right(st.length()-6));
            gotove.append(neg.left(neg.length()-1));
        } else if (st.contains("bool")||st.contains("Bool")){
            neg.append(st.right(st.length()-5));
            gotove.append(neg.left(neg.length()-1));
        }
        QStringList spl = gotove.split(",", QString::SkipEmptyParts);
        for (int i=0; i<spl.length(); i++){
            if (i==spl.length()-1){
                st.append("cin >> ");
                st.append(spl.at(i));
                st.append("\n");
            } else {
            st.append("cin >> ");
            st.append(spl.at(i)+";");
            st.append("\n");
            }
        }

    }
    return st;
}
QString Generator::getYesArKod(QString s, QString s1){
    QString st;
    st.append("if ("+s+"){\n"+s1+
                       "\n} ");
    return st;
}
QString Generator::getNoArKod(QString s){
    QString st;
    st.append("else {\n"+s+"\n}");
    return st;
}
QString Generator::getGotoveIf2(Arrow *ar){
    QString resultif, textel="", ifin = qgraphicsitem_cast<ActionBars*>(ar->endItem())->getString();
    kinec=false;
    if (ar->endItem()->getString().contains("..")){
        QString rez; ActionBars *oporacycle; bool kinecarnoc=false;
        kinecaryes=false;
        rez = getCycleString(ar->endItem()->getString());
        foreach (Arrow *item, qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows()) {
            if (item->type()==Arrow::Type && item->getMode()==Arrow::YesArrow){
                oporacycle=qgraphicsitem_cast<ActionBars *>(item->endItem());
                while(kinecaryes==false){
                    Arrow *aryes;
                    foreach (Arrow *item2, oporacycle->getPochArrows()){
                    if (item2->type()==Arrow::Type && item2->getMode()==Arrow::YesArrow){
                     aryes = item2;
                    } else if (item2->type()==Arrow::Type && item2->getMode()==Arrow::DefArrow){
                        aryes = item2;
                    }
                    }
                    if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType()==ActionBars::Conditions){

                        kinecaryes=true;

                    } else {
                        if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::danih){
                            rez.append(getKod(qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getString())+"\n");
                        } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::Priam){
                            rez.append(qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getString()+"\n");
                        } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::Conditions){
                            rez.append(getGotoveIf(aryes));
                        }
                        oporacycle=qgraphicsitem_cast<ActionBars*>(aryes->endItem()->getKinArrows().last()->endItem());
                    }
                }
                rez.append("}\n");
                kinecaryes=false;
        }
        }
        foreach (Arrow *item, qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows()) {
            if (item->type()==Arrow::Type && item->getMode()==Arrow::NoArrow){
                oporacycle=qgraphicsitem_cast<ActionBars *>(item->endItem());
                while(kinecarnoc==false){
                    Arrow *arno;
                    foreach (Arrow *item2, oporacycle->getPochArrows()){
                    if (item2->type()==Arrow::Type && item2->getMode()==Arrow::NoArrow){
                     arno = item2;
                    } else if (item2->type()==Arrow::Type && item2->getMode()==Arrow::DefArrow){
                        arno = item2;
                    }
                    }
                    if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType()==ActionBars::kinec){
                        kinecarnoc=true;

                    } else {
                        if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType() == ActionBars::danih){
                            rez.append(getKod(qgraphicsitem_cast<ActionBars*>(arno->endItem())->getString())+"\n");
                        } else if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType() == ActionBars::Priam){
                            rez.append(qgraphicsitem_cast<ActionBars*>(arno->endItem())->getString()+"\n");
                        } else if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType() == ActionBars::Conditions){
                            rez.append(getGotoveIf(arno));
                            oporacycle=qgraphicsitem_cast<ActionBars*>(arno->endItem()->getKinArrows().first()->endItem());
                        }
                        oporacycle=qgraphicsitem_cast<ActionBars*>(arno->endItem()->getKinArrows().first()->endItem());
                    }
                }
        }
        }
        return rez;
    } else {
    if (qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows().isEmpty()){
        resultif = getYesArKod(ifin, textel);
        return resultif;
    } else if(qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows().count()==1){
        return ("Програма не підтримує розміщення блоку умови з однією стрілкою");
    } else {
    foreach (Arrow *item, qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows()) {
        if (item->type()==Arrow::Type && item->getMode()==Arrow::YesArrow){
            oporaif=qgraphicsitem_cast<ActionBars *>(item->endItem());
            while(kinec==false) {
                Arrow *aryes;
                foreach (Arrow *item2, oporaif->getPochArrows()){
                if (item2->type()==Arrow::Type && item2->getMode()==Arrow::YesArrow){
                 aryes = item2;
                } else if (item2->type()==Arrow::Type && item2->getMode()==Arrow::DefArrow){
                    aryes = item2;
                }
                }
                if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getPochArrows().count()>=2 && !(qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType()==ActionBars::kinec)){
                    kinec=true; kinecnepol=true; ar2=aryes;
                } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getPochArrows().count()>=2 && (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType()==ActionBars::kinec)){
                    kinec=true;
                } else {
                    if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::danih){
                        textel.append(getKod(qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getString())+"\n");
                    } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::Priam){
                        textel.append(qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getString()+"\n");

                    } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::Conditions){

                        textel.append(getGotoveIf2(aryes));
                        oporaif=qgraphicsitem_cast<ActionBars*>(aryes->endItem()->getKinArrows().first()->endItem());
                    }
                    oporaif=qgraphicsitem_cast<ActionBars*>(aryes->endItem()->getKinArrows().first()->endItem());

                }
            }

}
}
    kinec=false;
    resultif = getYesArKod(ifin, textel);
    textel.clear();
    foreach (Arrow *item, qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows()) {
        if (item->type()==Arrow::Type && item->getMode()==Arrow::NoArrow){
            oporaif=qgraphicsitem_cast<ActionBars *>(item->endItem());;
            while(kinec==false) {
                Arrow *arno;
                foreach (Arrow *item2, oporaif->getPochArrows()){
                if (item2->type()==Arrow::Type && item2->getMode()==Arrow::NoArrow){
                 arno = item2;
                } else if (item2->type()==Arrow::Type && item2->getMode()==Arrow::DefArrow){
                    arno = item2;
                }
                }
                if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getPochArrows().count()>=2 && !(qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType()==ActionBars::kinec)){
                    kinec=true; kinecnepol=true; ar2=arno;
                } else if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getPochArrows().count()>=2 && (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType()==ActionBars::kinec)){
                    kinec=true;
                } else {
                    if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType() == ActionBars::danih){
                        textel.append(getKod(qgraphicsitem_cast<ActionBars*>(arno->endItem())->getString())+"\n");
                    } else if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType() == ActionBars::Priam){
                        textel.append(qgraphicsitem_cast<ActionBars*>(arno->endItem())->getString()+"\n");

                    } else if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType() == ActionBars::Conditions){

                        textel.append(getGotoveIf2(arno));
                        oporaif=qgraphicsitem_cast<ActionBars*>(arno->endItem()->getKinArrows().first()->endItem());
                    }
                    oporaif=qgraphicsitem_cast<ActionBars*>(arno->endItem()->getKinArrows().first()->endItem());

                }
            }

}
}
}

    resultif.append(getNoArKod(textel));
    textel.clear();
    return resultif;
    }
    return 0;
}

QString Generator::getGotoveIf(Arrow *ar){
    QString resultif, textel, ifin = qgraphicsitem_cast<ActionBars*>(ar->endItem())->getString();

    if (qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows().isEmpty()){

    } else if(qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows().count()==1){
        return ("Програма не підтримує розміщення блоку умови з однією стрілкою");
    } else {
    foreach (Arrow *item, qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows()) {
        if (item->type()==Arrow::Type && item->getMode()==Arrow::YesArrow){
            oporaif=qgraphicsitem_cast<ActionBars *>(item->endItem());
            kinec=false;
            while(kinec==false){
                Arrow *aryes;
                foreach (Arrow *item2, oporaif->getPochArrows()){
                if (item2->type()==Arrow::Type && item2->getMode()==Arrow::YesArrow){
                 aryes = item2;
                } else if (item2->type()==Arrow::Type && item2->getMode()==Arrow::DefArrow){
                    aryes = item2;
                }
                }
                if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getPochArrows().count()>=2){
                    kinec=true;
                } else {
                    if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::danih){
                        textel.append(getKod(qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getString())+"\n");
                    } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::Priam){
                        textel.append(qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getString()+"\n");
                    } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::Conditions){
                        textel.append(getGotoveIf2(aryes));
                        oporaif=qgraphicsitem_cast<ActionBars*>(aryes->endItem()->getKinArrows().last()->endItem());
                    }
                    oporaif=qgraphicsitem_cast<ActionBars*>(aryes->endItem()->getKinArrows().last()->endItem());
                }
            }
            if(kinecnepol==true) {
                oporaif2 = ar2->endItem();
                while (kinecnepol==true){
                    Arrow *aryes;
                    foreach (Arrow *item2, oporaif2->getPochArrows()){
                    if (item2->type()==Arrow::Type && item2->getMode()==Arrow::YesArrow){
                     aryes = item2;
                    } else if (item2->type()==Arrow::Type && item2->getMode()==Arrow::DefArrow){
                        aryes = item2;
                    }
                    }
                    if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getPochArrows().count()>=2 && qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType()==ActionBars::kinec){
                        kinecnepol=false;
                    } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getPochArrows().count()>=2){
                        kinecnepol=false;
                    } else {
                        if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::danih){
                            textel.append("\n"+getKod(qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getString())+"\n");
                        } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::Priam){
                            textel.append("\n"+qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getString()+"\n");
                        } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::Conditions){
                            textel.append("\n"+getGotoveIf2(aryes));
                            oporaif2=qgraphicsitem_cast<ActionBars*>(aryes->endItem()->getKinArrows().first()->endItem());
                        }
                        oporaif2=qgraphicsitem_cast<ActionBars*>(aryes->endItem()->getKinArrows().first()->endItem());
                    }
                }
            }
            kinecnepol=false;
            resultif = getYesArKod(ifin, textel);
            textel.clear();
            kinec=false;
            oporaif=0;
}
}

    foreach (Arrow *item, qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows()) {
        if (item->type()==Arrow::Type && item->getMode()==Arrow::NoArrow){
            oporaif=qgraphicsitem_cast<ActionBars *>(item->endItem());
            while(kinec==false){
                Arrow *arno;
                foreach (Arrow *item2, oporaif->getPochArrows()){
                if (item2->type()==Arrow::Type && item2->getMode()==Arrow::NoArrow){
                 arno = item2;
                } else if (item2->type()==Arrow::Type && item2->getMode()==Arrow::DefArrow){
                    arno = item2;
                }
                }
                if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getPochArrows().count()>=2){
                    kinec=true;
                } else {
                    if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType() == ActionBars::danih){
                        textel.append(getKod(qgraphicsitem_cast<ActionBars*>(arno->endItem())->getString())+"\n");
                    } else if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType() == ActionBars::Priam){
                        textel.append(qgraphicsitem_cast<ActionBars*>(arno->endItem())->getString()+"\n");
                    } else if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType() == ActionBars::Conditions){
                        textel.append(getGotoveIf2(arno));
                        oporaif=qgraphicsitem_cast<ActionBars*>(arno->endItem()->getKinArrows().first()->endItem());
                    }
                    oporaif=qgraphicsitem_cast<ActionBars*>(arno->endItem()->getKinArrows().first()->endItem());
                }
            }
            if(kinecnepol==true) {
                oporaif2 = ar2->endItem();
                while (kinecnepol==true){
                    Arrow *aryes;
                    foreach (Arrow *item2, oporaif2->getPochArrows()){
                    if (item2->type()==Arrow::Type && item2->getMode()==Arrow::NoArrow){
                     aryes = item2;
                    } else if (item2->type()==Arrow::Type && item2->getMode()==Arrow::DefArrow){
                        aryes = item2;
                    }
                    }
                    if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getPochArrows().count()>=2 && qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType()==ActionBars::kinec){
                        kinecnepol=false;
                    } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getPochArrows().count()>=2){
                        kinecnepol=false;
                    } else {
                        if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::danih){
                            textel.append("\n"+getKod(qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getString())+"\n");
                        } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::Priam){
                            textel.append("\n"+qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getString()+"\n");
                        } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::Conditions){
                            textel.append("\n"+getGotoveIf2(aryes));
                            oporaif2=qgraphicsitem_cast<ActionBars*>(aryes->endItem()->getKinArrows().first()->endItem());
                        }
                        oporaif2=qgraphicsitem_cast<ActionBars*>(aryes->endItem()->getKinArrows().first()->endItem());
                    }
                }
            }
            kinecnepol=false;
            resultif.append(getNoArKod(textel));
            return resultif;
            textel.clear();
            kinec=false;
            oporaif=0;
}
    }
    }
    return NULL;
}
void Generator::startProgram(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Зберегти код в файл"), "",
        tr("C++ Files (*.cpp *.h)"));
    QFile file(fileName);
    if (file.exists()){
        file.remove();
    }
    if(file.open(QIODevice::WriteOnly)){
        QTextStream cout(&file);
        cout << toPlainText();
        file.close();
    }
}

ActionBars* Generator::getOpora(Arrow *ar){
    ActionBars *oporaif, *opora;
    bool kinec3=false;
    if (qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows().isEmpty()){

    } else if(qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows().count()==1){

    } else {
    foreach (Arrow *item, qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows()) {
        if (item->type()==Arrow::Type && item->getMode()==Arrow::YesArrow){
            oporaif=qgraphicsitem_cast<ActionBars *>(item->endItem());
            while(kinec3==false){
                Arrow *aryes;
                foreach (Arrow *item2, oporaif->getPochArrows()){
                if (item2->type()==Arrow::Type && item2->getMode()==Arrow::YesArrow){
                 aryes = item2;
                } else if (item2->type()==Arrow::Type && item2->getMode()==Arrow::DefArrow){
                    aryes = item2;
                }
                }
                if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getPochArrows().count()>=2){
                    kinec3=true;
                    return opora=qgraphicsitem_cast<ActionBars*>(aryes->startItem());
                    oporaif=0;
                } else {
                    oporaif=qgraphicsitem_cast<ActionBars*>(aryes->endItem()->getKinArrows().first()->endItem());
                }
            }
        }
    }
    }
    return 0;
}
QString Generator::getCycleString(QString s){
    QString st;
    QStringList spl = s.split("..", QString::SkipEmptyParts);
    st.append("for (int "+spl.at(0)+"; "+s.at(0)+"<="+spl.at(1)+"; "+s.at(0)+"++){\n");
    return st;
}
ActionBars* Generator::getCyclOpora(Arrow *ar){
    ActionBars *oporacycle, *op; bool kinecarnoc=false;
    foreach (Arrow *item, qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows()) {
        if (item->type()==Arrow::Type && item->getMode()==Arrow::NoArrow){
            oporacycle=qgraphicsitem_cast<ActionBars *>(item->endItem());
            while(kinecarnoc==false){
                Arrow *arno;
                foreach (Arrow *item2, oporacycle->getPochArrows()){
                if (item2->type()==Arrow::Type && item2->getMode()==Arrow::NoArrow){
                 arno = item2;
                } else if (item2->type()==Arrow::Type && item2->getMode()==Arrow::DefArrow){
                    arno = item2;
                }
                }
                if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType()==ActionBars::kinec){
                    kinecarnoc=true;
                    op= qgraphicsitem_cast<ActionBars*>(arno->startItem());
                } else {
                    oporacycle=qgraphicsitem_cast<ActionBars*>(arno->endItem()->getKinArrows().first()->endItem());
                }
            }
    }
    }
    return op;
}
void Generator::Test2(){
    ActionBars *opora;
    clear();
    append(pochcod);
    foreach (QGraphicsItem *item, myScene->items()) {
        if (item->type()==ActionBars::Type){
            ++kilkistit;
        }
    }
    foreach (QGraphicsItem *item, myScene->items()) {
        if (item->type()==ActionBars::Type){
            if(qgraphicsitem_cast<ActionBars*>(item)->getDiagramType()==ActionBars::poch){
                opora = qgraphicsitem_cast<ActionBars*>(item);
            }
        }
    }
    if (!(kilkistit==0 || kilkistit==1) && !(opora->getKinArrows().isEmpty())){
        while(!(opora->getDiagramType()==ActionBars::kinec)){
            Arrow *ar = opora->getKinArrows().first();
            if ( qgraphicsitem_cast<ActionBars*>(ar->endItem())->getDiagramType() == ActionBars::danih){
                append(getKod(qgraphicsitem_cast<ActionBars*>(ar->endItem())->getString()));
                if (qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows().isEmpty()){
                    break;
                }
                opora=qgraphicsitem_cast<ActionBars*>(ar->endItem());
            } else if (qgraphicsitem_cast<ActionBars*>(ar->endItem())->getDiagramType() == ActionBars::Priam){
                append(qgraphicsitem_cast<ActionBars*>(ar->endItem())->getString());
                if (qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows().isEmpty()){
                    break;
                }
                opora=qgraphicsitem_cast<ActionBars*>(ar->endItem());
            } else if (qgraphicsitem_cast<ActionBars*>(ar->endItem())->getDiagramType() == ActionBars::Conditions){
                if (ar->endItem()->getString().contains("..")){
                    QString rez; ActionBars *oporacycle; bool kinecarnoc=false;
                    rez = getCycleString(ar->endItem()->getString());
                    append(rez);
                    foreach (Arrow *item, qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows()) {
                        if (item->type()==Arrow::Type && item->getMode()==Arrow::YesArrow){
                            oporacycle=qgraphicsitem_cast<ActionBars *>(item->endItem());
                            while(kinecaryes==false){
                                Arrow *aryes;
                                foreach (Arrow *item2, oporacycle->getPochArrows()){
                                if (item2->type()==Arrow::Type && item2->getMode()==Arrow::YesArrow){
                                 aryes = item2;
                                } else if (item2->type()==Arrow::Type && item2->getMode()==Arrow::DefArrow){
                                    aryes = item2;
                                }
                                }
                                if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType()==ActionBars::Conditions){

                                    kinecaryes=true;
                                    foreach (QGraphicsItem *item, myScene->items()) {
                                        if (item->type()==ActionBars::Type){
                                            if(qgraphicsitem_cast<ActionBars*>(item)->getDiagramType()==ActionBars::kinec){
                                                opora = qgraphicsitem_cast<ActionBars*>(item)->getPochArrows().first()->startItem();
                                            }
                                        }
                                    }
                                    QMessageBox *msg = new QMessageBox;
                                    msg->setText("1");
                                    msg->exec();

                                } else {
                                    if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::danih){
                                        append(getKod(qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getString())+"\n");
                                    } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::Priam){
                                        append(qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getString()+"\n");
                                    } else if (qgraphicsitem_cast<ActionBars*>(aryes->endItem())->getDiagramType() == ActionBars::Conditions){
                                        append(getGotoveIf(aryes));
                                    }
                                    oporacycle=qgraphicsitem_cast<ActionBars*>(aryes->endItem()->getKinArrows().last()->endItem());
                                }
                            }
                            append("}\n");
                            kinecaryes=false;
                    }
                    }
                    foreach (Arrow *item, qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows()) {
                        if (item->type()==Arrow::Type && item->getMode()==Arrow::NoArrow){
                            oporacycle=qgraphicsitem_cast<ActionBars *>(item->endItem());
                            while(kinecarnoc==false){
                                Arrow *arno;
                                foreach (Arrow *item2, oporacycle->getPochArrows()){
                                if (item2->type()==Arrow::Type && item2->getMode()==Arrow::NoArrow){
                                 arno = item2;
                                } else if (item2->type()==Arrow::Type && item2->getMode()==Arrow::DefArrow){
                                    arno = item2;
                                }
                                }
                                if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType()==ActionBars::kinec){
                                    kinecarnoc=true;

                                } else {
                                    if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType() == ActionBars::danih){
                                        append(getKod(qgraphicsitem_cast<ActionBars*>(arno->endItem())->getString())+"\n");
                                    } else if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType() == ActionBars::Priam){
                                        append(qgraphicsitem_cast<ActionBars*>(arno->endItem())->getString()+"\n");
                                    } else if (qgraphicsitem_cast<ActionBars*>(arno->endItem())->getDiagramType() == ActionBars::Conditions){
                                        append(getGotoveIf(arno));
                                        oporacycle=qgraphicsitem_cast<ActionBars*>(arno->endItem()->getKinArrows().first()->endItem());
                                    }
                                    oporacycle=qgraphicsitem_cast<ActionBars*>(arno->endItem()->getKinArrows().first()->endItem());
                                }
                            }
                    }
                    }
                } else {
                QString ifin = qgraphicsitem_cast<ActionBars*>(ar->endItem())->getString(), textel="";
                if (qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows().isEmpty()){
                    append(getYesArKod(ifin, textel));
                    break;
                } else if(qgraphicsitem_cast<ActionBars *>(ar->endItem())->getKinArrows().count()==1){
                    append("Покищо блок умови не може бути з одною стрілкою");
                    break;
                } else{
                QString resultif = getGotoveIf(ar);
                append(resultif);
                opora = getOpora(ar);
                }
                }
            } else if (qgraphicsitem_cast<ActionBars*>(ar->endItem())->getDiagramType() == ActionBars::kinec){
                append(kincod);
                opora=qgraphicsitem_cast<ActionBars*>(ar->endItem());
            }
        }
    }
    opora=0;
    kilkistit=0;
}
