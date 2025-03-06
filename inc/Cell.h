#ifndef CELL_H
#define CELL_H

enum CellType {alive, dead};

class Cell {
public:
    explicit Cell(const CellType input_type = dead) : type_(input_type){};

    [[nodiscard]] CellType get_type() const {return type_;}

    void set_type(const CellType input_type) {type_ = input_type;}

    [[nodiscard]]  bool isAlive() const {
        return type_ == alive;
    };

    bool operator==(const Cell& rhs) const {return rhs.type_ == this->type_;}

    bool operator!=(const Cell& rhs) const {return rhs.type_ != this->type_;}

private:
	CellType type_;
};

#endif //CELL_H
