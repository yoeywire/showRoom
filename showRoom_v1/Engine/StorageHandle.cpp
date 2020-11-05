#include "StorageHandle.h"


std::ostream& operator<<(std::ostream& os, const Effect& fx)
{
    os << fx.name << std::endl;
    os << fx.form << std::endl;
    os << fx.direction << std::endl;
    os << fx.bpm << std::endl;
    os << fx.rate << std::endl;
    os << fx.phase << std::endl;
    os << fx.high << std::endl;
    os << fx.low << std::endl;
    os << fx.dutycycle << std::endl;
    os << fx.groups << std::endl;
    os << fx.blocks << std::endl;
    os << fx.wings << std::endl;
    os << fx.color;

    return os;
}


std::istream& operator>>(std::istream& is, const Effect& fx)
{
    return is;
}


std::ostream& operator<<(std::ostream& os, const RgbColor& col) {
    os << std::to_string(col.r) << std::endl;
    os << std::to_string(col.g) << std::endl;
    os << std::to_string(col.b);
    return os;
}



StorageHandle::StorageHandle() 
{

}

StorageHandle::~StorageHandle() 
{

}



// Function that reads an effect to a file
Effect StorageHandle::getEffect(uint16_t effNum) 
{
    Effect effect;

    std::ifstream input(getFileName(EFFECT, effNum));
    wxLogDebug("<StorageHandle> Reading from: %s", getFileName(EFFECT, effNum));

    std::string line; 
    
    getline(input, line);
    wxLogDebug("<StorageHandle> Reading name of effect: %s", line); 
    effect.name = line;
    
    getline(input, line);
    wxLogDebug("<StorageHandle> Reading form of effect: %s", line);

        
    
    return effect;
}



// Function that stores an effect to a file
bool StorageHandle::setEffect(uint16_t effNum, Effect effect)
{
    std::string fileName = getFileName(EFFECT, effNum);
    std::ofstream output(fileName);
    wxLogDebug("<StorageHandle> Writing to: %s", fileName);

    //output.open(fileName, std::ofstream::out | std::ofstream::trunc);

    if (output.is_open()) {
        output << effect;
    }
    else {
        return false;
    }

    return true;
}



// Function that returns the name of the file, dependent on the tyoe and ID
std::string StorageHandle::getFileName(FileType type, uint16_t num) 
{
    std::string name;
    name.append("userdata/");


    switch (type)
    {
    case EFFECT:
        name.append("effects/fx");
        name.append(std::to_string(num));
        name.append(".txt");
        break;
    }


    return name;
}