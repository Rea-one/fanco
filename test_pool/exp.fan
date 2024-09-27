
.to.int|fm.前移

.to.int|pm.后移

fm.fan.
    int.minus.1
end

pm.fan.
    int.add.1
end

stack.fan.
    core.fan.group
    top.fan.int
end

data.to.stack|push.压栈
    stack_top.set.data
    .pm.top_stack
end

stack.to.data|pop.出栈
    data.set.stack_top
    .fm.top_stack
end

stack.to.bool|empty.判空
    stack_top.eq.0
    bool.set.sez
end