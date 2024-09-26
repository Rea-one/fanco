
.to.int|fm.前移

.to.int|pm.后移

fm.def.
    int.minus.1
end

pm.def.
    int.add.1
end

stack.have.
    core.t.t_group
    top.t.int
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