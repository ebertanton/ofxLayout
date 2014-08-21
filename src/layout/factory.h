//
//  factory.h
//  playlistTest
//
//  Created by Osiloke Emoekpere on 8/11/14.
//
//

#ifndef playlistTest_factory_h
#define playlistTest_factory_h

#include "layout.h"
#include "overlay.h"
#include "column.h"
#include "row.h"


class LayoutFactory{
private:
    std::map<std::string, FluidLayout::Ptr> m_layouts;
    vector<FluidLayout::Ptr> playlists;
public:
    LayoutFactory(){
        
    };
    
    FluidLayout::Ptr getLayout(std::string name){
        std::map<std::string, FluidLayout::Ptr>::iterator found;
        found = m_layouts.find(name);
        if (found != m_layouts.end()){
            return found->second;
        }
        
    };
    
    template<class T>
    shared_ptr<T> createLayout(std::string name)
    {
        shared_ptr<T> layout = shared_ptr<T>(new T(name));
        m_layouts.insert(std::pair<std::string, FluidLayout::Ptr>(name, layout));
        return layout;
    }
    
    
    FluidLayout::Ptr create(std::string name, std::string type){
        if (type == "overlay"){
            FluidLayout::Ptr layout = createLayout<OverlayLayout>(name);
            return layout;
        }else if(type == "row"){
            FluidLayout::Ptr layout = createLayout<RowLayout>(name);
            return layout;
        }else if(type == "column"){
            FluidLayout::Ptr layout = createLayout<ColumnLayout>(name);
            return layout;
        }else{
            FluidLayout::Ptr layout = createLayout<FluidLayout>(name);
            return layout;
        }

    }
    
    typedef shared_ptr<FluidLayout> Ptr;
};
#endif
