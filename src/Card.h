//
// Created by Michael Hodge on 5/10/21.
//

#ifndef UNO_CARD_H
#define UNO_CARD_H


class Card {
public:
    enum Color {Red, Green, Blue, Yellow, COLOR_COUNT};
    enum Value {Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Skip, Reverse, Draw2, Wild, Wild_draw4, VALUE_COUNT};

    Color CardColor;
    Value CardValue;

    Card(Color cardColor, Value cardValue);
};


#endif //UNO_CARD_H
