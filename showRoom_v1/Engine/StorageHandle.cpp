#include "StorageHandle.h"



StorageHandle::StorageHandle() 
{

}

StorageHandle::~StorageHandle() 
{

}



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



bool StorageHandle::setEffect(uint16_t effNum, Effect effect)
{
    std::string fileName = getFileName(EFFECT, effNum);
    std::ofstream output(fileName);
    wxLogDebug("<StorageHandle> Writing to: %s", fileName);

    //output.open(fileName, std::ofstream::out | std::ofstream::trunc);

    if (output.is_open()) {
        output << effect.name << "\n";
        output << std::to_string(effect.form) << "\n";
        output << std::to_string(effect.bpm) << "\n";
        output << std::to_string(effect.rate) << "\n";
        output << std::to_string(effect.phase) << "\n";
        output << std::to_string(effect.groups) << "\n";
        output << std::to_string(effect.blocks) << "\n";
        output << std::to_string(effect.wings) << "\n";
        output << std::to_string(effect.color.r) << "\n";
        output << std::to_string(effect.color.g) << "\n";
        output << std::to_string(effect.color.b) << "\n";
        output.close();
    }
    else {
        return false;
    }

    return true;
}



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