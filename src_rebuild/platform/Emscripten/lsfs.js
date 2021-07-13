// Reusing all MEMFS functionality
// additionaly read data at mount
// and save data at some operations.
// Intended to use only for small files (like game settings),
// because LocalStorage is very limited
// and data saved as text in JSON format.

function LSFS() {
  if (LSFS.mount) {
    return LSFS;
  }

  var wrapCreateNode = wrapNode(MEMFS.createNode);

  var wrap_node_ops = {
    setattr: wrapSave(MEMFS.node_ops.setattr),
    mknod: wrapNode(MEMFS.node_ops.mknod),
    rename: wrapSave(MEMFS.node_ops.rename),
    unlink: wrapSave(MEMFS.node_ops.unlink),
    rmdir: wrapSave(MEMFS.node_ops.rmdir),
    symlink: wrapNode(MEMFS.node_ops.symlink)
  };

  var wrap_stream_ops = {
    write: wrapSave(MEMFS.stream_ops.write),
    msync: wrapSave(MEMFS.stream_ops.msync)
  };

  var props = [ 'name', 'mode', 'rdev', 'link', 'usedBytes', 'timestamp' ];

  LSFS.mount = mount;

  return LSFS;

  function wrapNode(fn) {
    return function() {
      var node = fn.apply(null, arguments);
      setupNode(node);
      return node;
    }
  }

  function wrapSave(fn) {
    return function(node) {
      var res = fn.apply(null, arguments);
      save(node);
      return res;
    }
  }

  function setupNode(node) {
    var node_ops = {};
    for (var op in node.node_ops) {
      node_ops[op] = wrap_node_ops[op] || node.node_ops[op];
    }
    node.node_ops = node_ops;

    var stream_ops = {};
    for (var op in node.stream_ops) {
      stream_ops[op] = wrap_stream_ops[op] || node.stream_ops[op];
    }
    node.stream_ops = stream_ops;
  }

  function filter(node) {
    var result = {};
    for (var key in node) {
      if (props.indexOf(key) !== -1) {
        result[key] = node[key];
      }
    }

    if (node.contents) {
      if (node.contents.length) {
        result.contents = Array.apply([], node.contents);
      } else {
        result.contents = {};
        for (var name in node.contents) {
          result.contents[name] = filter(node.contents[name]);
        }
      }
    }

    return result;
  }

  function save(node) {
    if (node.node) {
      node = node.node;
    }

    var mount = node.mount;
    if (!mount || !mount.opts || !mount.opts.key) {
      return;
    }

    try {
      localStorage.setItem(mount.opts.key, JSON.stringify(filter(mount.root)));
    } catch (err) {}
  }

  function mount(mount) {
    if (!mount.opts || !mount.opts.key) {
      return;
    }

    var data;
    try {
      data = localStorage.getItem(mount.opts.key);
    } catch (err) {}
    if (data) {
      try {
        data = JSON.parse(data);
      } catch (err) {}
    }

    var node = MEMFS.mount(mount);
    setupNode(node);
    load(node, mount, data);

    return node;
  }

  function load(node, mount, data) {
    node.mount = mount;
    if (!data) {
      return;
    }
    for (var key in data) {
      if (props.indexOf(key) !== -1) {
        node[key] = data[key];
      }
    }
    if (data.contents) {
      if (data.contents.length) {
        node.contents = data.contents;
      } else {
        node.contents = {};
        for (var name in data.contents) {
          var childData = data.contents[name];
          var childNode = wrapCreateNode(node, name, childData.mode, childData.rdev);
          load(childNode, mount, childData);
        }
      }
    }
  }
}