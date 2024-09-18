function createImport(impt, index) {
  const imptPath = JSONStringify(impt);
  return `import * as $import_${index} from ${imptPath};
import.meta.imports[${imptPath}] = $import_${index};`;
}

/**
 * Creates an export for a given module.
 * @param {string} expt - The name of the export.
 * @param {number} index - The index of the export statement.
 */
function createExport(expt, index) {
  const nameStringLit = JSONStringify(expt);
  return `let $export_${index};
export { $export_${index} as ${nameStringLit} };
import.meta.exports[${nameStringLit}] = {
  get: () => $export_${index},
  set: (v) => $export_${index} = v,
};`;
}

/**
 * Creates a dynamic module with the given imports, exports, URL, and evaluate function.
 * @param {string[]} imports - An array of imports.
 * @param {string[]} exports - An array of exports.
 * @param {string} [url=''] - The URL of the module.
 * @param {(reflect: DynamicModuleReflect) => void} evaluate - The function to evaluate the module.
 * @typedef {object} DynamicModuleReflect
 * @property {string[]} imports - The imports of the module.
 * @property {string[]} exports - The exports of the module.
 * @property {(cb: (reflect: DynamicModuleReflect) => void) => void} onReady - Callback to evaluate the module.
 */
const createDynamicModule = (imports, exports, url = '', evaluate) => {
  debug('creating ESM facade for %s with exports: %j', url, exports);
  const source = `
${ArrayPrototypeJoin(ArrayPrototypeMap(imports, createImport), '\n')}
${ArrayPrototypeJoin(ArrayPrototypeMap(exports, createExport), '\n')}