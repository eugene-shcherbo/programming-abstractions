using System;
using Xunit;

namespace FindDuplicate
{
    public class Tests
    {
        [Fact]
        public void NoDuplicateOrNotCorrectSequenceThrowsException()
        {
            Assert.Throws<ArgumentException>(
                () => FindDuplicateAlgorithm.FindDuplicate(new[] { 1, 2, 3 }));

            Assert.Throws<ArgumentException>(
                () => FindDuplicateAlgorithm.FindDuplicate(new[] { 1, 5, 5 }));
        }

        [Fact]
        public void CorrectlyFindFirstDuplicate()
        {
            var values = new[] { 3, 5, 1, 5, 4, 3 };
            Assert.Equal(5, FindDuplicateAlgorithm.FindDuplicate(values));
        }

        [Fact]
        public void FindDuplicateWhen1Duplicated()
        {
            var values = new[] { 1, 5, 1, 5, 4, 3 };
            Assert.Equal(1, FindDuplicateAlgorithm.FindDuplicate(values));
        }

        [Fact]
        public void FindDuplicateWhenTheBiggestValueDuplicated()
        {
            var values = new[] { 2, 5, 1, 3, 4, 5 };
            Assert.Equal(5, FindDuplicateAlgorithm.FindDuplicate(values));
        }
    }
}
