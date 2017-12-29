open Mocha;

describe("List", () => {
  describe("List.map", () => {
    it("should map the values", () => {
      expect(List.map((*)(2), [1,2,3])).to_be([2,4,6]);
    });
    it("should work with an empty list", () => {
      expect(List.map((*)(2), [])).to_be([]);
    });
  });
  describe("List.fold_left", () => {
    it("should do a left fold", () => {
      expect(List.fold_left((+), 0, [1,2,3,4])).to_be(10);
    });
    it("should work with an empty list", () => {
      expect(List.fold_left((+), 0, [])).to_be(0);
    });
  })
})
