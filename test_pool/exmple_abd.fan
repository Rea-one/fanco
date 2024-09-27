
tar
[
    sub,obj,i,you

]

action
[
    i.to.dream 
]

stream
[
    leek.fan.sub
    leek.set.1



]

htlist.def.
    list.t.ints
    left.t.int
    right.t.int
end


core_pack.def.
    list.t.ints
    left.t.int
    right.t.int
    pivot.t.int
end

core_pack.to.devide|core.快排核心
    pack_left.less.pack_right|loop0
        pack_left.less.pack_right & pack_right.more.pack_pivot|loop1
            pack_right_s.minus.1
        lend
        pack_left.exchange.pack_right
        pack_left.less.pack_right & pack_left.less.pack_pivot|loop1
            pack_left_s.plus.1
        lend
        pack_left.exchange.pack_right
    lend
    pack_left.set.pack_pivot
end.pack_left_s


htlist.to.list|quick.快速排序
    list_left.add.list_right
    llalr.ecpt.2|pivot
    pivot.more.left|branch0
        list_piovt.exchange.list_left
    cend
    stand.set.list_left
    .core.core_pack
    .quick.(htlist_list..htlist_left..ccp.minus.1)
    .quick.(htlist_list..ccp.add.1..htlist_right)
end
    
    

min.is.ints.give.int

min.fan.
  branch0..ints_0.less,ints_1
  true..int.set.ints_0
  false..int.set.ints_1
end